#include "../Header.h"

#include "Map.h"

const int boxVertexIndices[8][3] =
{
    { 0, 0, 0 },
    { 1, 0, 0 },
    { 1, 0, 1 },
    { 0, 0, 1 },
    { 0, 1, 0 },
    { 1, 1, 0 },
    { 1, 1, 1 },
    { 0, 1, 1 }
};

const int triangleVertexIndices[12][3] =
{
    { 0, 1, 2 },
    { 0, 2, 3 },
    { 1, 5, 6 },
    { 1, 6, 2 },
    { 5, 4, 7 },
    { 5, 7, 6 },
    { 4, 0, 3 },
    { 4, 3, 7 },
    { 3, 2, 6 },
    { 3, 6, 7 },
    { 4, 5, 1 },
    { 4, 1, 0 }
};

const int vertexTextureUVIndices[6][2] =
{
    { 0, 0 },
    { 1, 0 },
    { 1, 1 },
    { 0, 0 },
    { 1, 1 },
    { 0, 1 },
};

Map::Map(const std::string name)
{
    std::string mapFilePath = std::format("Assets/Maps/{}.json", name);
    std::ifstream mapFile(mapFilePath);

    if (!mapFile.is_open())
    {
        std::string errorMessage = std::format("Cannot Open Map File ({}).", mapFilePath);
        std::cout << errorMessage << std::endl;
        throw std::exception(errorMessage.c_str());
    }

    Json json = Json::parse(mapFile);
    this->mapJsonObjects = json["mapObjects"].get<std::vector<MapJsonObject>>();
    this->mapTextures = json["textures"].get<std::vector<std::string>>();
}

void Map::Generate(std::vector<BoundingBox>& boundingBoxes, std::vector<std::vector<Vertex>>& orderedVertices, std::vector<Texture>& textures, std::vector<VertexBuffer>& vbos)
{
    this->validMapJsonObjects();

    //         7-------6
    //  3D    /|      /|               2D
    //       3-------2 |                    3---2
    //       | |     | |     Z  Y           |  /|
    //       | 4-----|-5     | /            | / |
    //       |/      |/      |/             |/  |
    //       0-------1       ----- X        0---1

    std::vector<Vertex> vertices;

    for (const MapJsonObject& object : this->mapJsonObjects)
    {
        if (object.type == MapJsonObjectType::LIGHT)
        {
            // TODO
            continue;
        }

        BoundingBox boundingBox = BoundingBox::FromTwoPoints(object.points[0], object.points[1]);
        boundingBoxes.push_back(boundingBox);

        if (object.type == MapJsonObjectType::TRIGGER)
            continue;

        glm::vec3 pos[2] = { boundingBox.min, boundingBox.max };
        float cubicVertexPos[8][3] = {  };

        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 3; j++)
                cubicVertexPos[i][j] = pos[boxVertexIndices[i][j]][j];

        for (int i = 0; i < 12; i++)
        {
            const int* indices = triangleVertexIndices[i];
            int uvIndex = i % 2;
            const MapJsonTextureUV* textureUV = &object.textureUV[i / 2];

            for (int j = 0; j < 3; j++)
            {
                Vertex vertex;

                vertex.position = glm::vec3(cubicVertexPos[indices[j]][0], cubicVertexPos[indices[j]][1], cubicVertexPos[indices[j]][2]);
                vertex.color = object.color;
                vertex.color /= 255.0f;
                
                if (object.useTexture && object.textureID >= 0)
                {
                    int u = vertexTextureUVIndices[uvIndex * 3 + j][0];
                    int v = vertexTextureUVIndices[uvIndex * 3 + j][1];

                    vertex.textureUV = glm::vec2(
                        u == 0 ? textureUV->bottomLeft.x : textureUV->topRight.x,
                        v == 0 ? textureUV->bottomLeft.y : textureUV->topRight.y
                    );

                    vertex.textureID = object.textureID;
                }

                vertices.push_back(vertex);
            }
        }
    }

    textures = this->loadTextures();
    orderedVertices = std::vector<std::vector<Vertex>>(textures.size() + 1);

    for (const Vertex& vertex : vertices)
        orderedVertices[vertex.textureID + 1].push_back(vertex);

    for (std::vector<Vertex>& vs : orderedVertices)
    {
        VertexBuffer vbo(vs);
        vbos.push_back(vbo);
    }
}

void Map::validMapJsonObjects()
{
    size_t textureCount = this->mapTextures.size();

    for (MapJsonObject& object : this->mapJsonObjects)
        if (object.textureID >= textureCount)
        {
            object.textureID = -1;
            object.useTexture = false;
        }
}

std::vector<Texture> Map::loadTextures()
{
    int textureCount = this->mapTextures.size();
    std::vector<Texture> textures;

    for (int i = 0; i < textureCount; i++)
    {
        Texture texture(std::format("Assets/Textures/{}", this->mapTextures[i]));

        textures.push_back(texture);
    }

    return textures;
}
