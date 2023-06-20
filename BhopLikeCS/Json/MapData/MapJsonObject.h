#pragma once

#include "../Header.h"

#include "MapJsonTextureUV.h"

enum MapJsonObjectType
{
    BLOCK,
    LIGHT,
    TRIGGER
};

NLOHMANN_JSON_SERIALIZE_ENUM(MapJsonObjectType,
                                { { MapJsonObjectType::BLOCK, "block" },
                                { MapJsonObjectType::LIGHT, "light" },
                                { MapJsonObjectType::TRIGGER, "trigger" } });

enum MapJsonObjectTriggerType
{
    NONE,
    TELEPORT,
    STARTTIMER,
    ENDTIMER
};

NLOHMANN_JSON_SERIALIZE_ENUM(MapJsonObjectTriggerType,
                                { { MapJsonObjectTriggerType::NONE, nullptr },
                                { MapJsonObjectTriggerType::TELEPORT, "teleport" },
                                { MapJsonObjectTriggerType::STARTTIMER, "startTimer" },
                                { MapJsonObjectTriggerType::ENDTIMER, "endTimer" } });

struct MapJsonObject
{
    MapJsonObjectType type;
    std::vector<glm::vec3> points = std::vector<glm::vec3>(2);
    glm::u8vec3 color = glm::u8vec3(255);
    int textureID = -1;
    std::vector<MapJsonTextureUV> textureUV = std::vector<MapJsonTextureUV>(6);
    bool useTexture = true;

    friend void from_json(const Json& json, MapJsonObject& object)
    {
        MapJsonObject defaultObject;

        FROM_JSON_WITH_DEFAULT(type);
        FROM_JSON_WITH_DEFAULT(points);
        FROM_JSON_WITH_DEFAULT(color);
        FROM_JSON_WITH_DEFAULT(textureID);
        FROM_JSON_WITH_DEFAULT(textureUV);
        FROM_JSON_WITH_DEFAULT(useTexture);
    }

    friend void to_json(Json& json, const MapJsonObject& object)
    {
        TO_JSON(type);
        TO_JSON(points);
        TO_JSON(color);
        TO_JSON(textureID);
        TO_JSON(textureUV);
        TO_JSON(useTexture);
    }
};
