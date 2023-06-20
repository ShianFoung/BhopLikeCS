#pragma once

#include "../Header.h"

struct GameSettings
{
	int tickrateAndFps = 128;
	std::string map = "bhop_test";

    friend void from_json(const Json& json, GameSettings& object)
    {
        GameSettings defaultObject;

        FROM_JSON_WITH_DEFAULT(tickrateAndFps);
        FROM_JSON_WITH_DEFAULT(map);
    }

    friend void to_json(Json& json, const GameSettings& object)
    {
        TO_JSON(tickrateAndFps);
        TO_JSON(map);
    }
};