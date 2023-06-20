#pragma once

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 textureUV;
    int textureID = -1;

    constexpr Vertex() = default;

    inline constexpr Vertex& operator=(const Vertex& vertex)
    {
        this->position = vertex.position;
        this->color = vertex.color;
        this->textureUV = vertex.textureUV;
        this->textureID = vertex.textureID;

        return *this;
    }
};
