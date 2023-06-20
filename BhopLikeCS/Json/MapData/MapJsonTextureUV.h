#pragma once

#include "../Header.h"

struct MapJsonTextureUV
{
    glm::vec2 bottomLeft;
    glm::vec2 topRight = glm::vec2(1.0f);

    friend void from_json(const Json& json, MapJsonTextureUV& object)
    {
        MapJsonTextureUV defaultObject;

        FROM_JSON_WITH_DEFAULT(bottomLeft);
        FROM_JSON_WITH_DEFAULT(topRight);
    }

    friend void to_json(Json& json, const MapJsonTextureUV& object)
    {
        TO_JSON(bottomLeft);
        TO_JSON(topRight);
    }
};
