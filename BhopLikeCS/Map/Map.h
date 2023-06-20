#pragma once

#include "../Json/MapData/MapJsonObject.h"
#include "../Data/BoundingBox.h"
#include "../Graphics/Data/Vertex.h"
#include "../Texture.h"
#include "../Graphics/Memory/VertexArray.h"
#include "../Graphics/Memory/VertexBuffer.h"

class Map
{
public:
    Map(const std::string name);

    void Generate(std::vector<BoundingBox>& boundingBoxes, std::vector<std::vector<Vertex>>& orderedVertices, std::vector<Texture>& textures, std::vector<VertexBuffer>& vbos);
private:
    std::vector<MapJsonObject> mapJsonObjects;
    std::vector<std::string> mapTextures;

    void validMapJsonObjects();
    std::vector<Texture> loadTextures();
};
