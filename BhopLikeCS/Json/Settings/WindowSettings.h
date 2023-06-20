#pragma once

#include "../Header.h"

struct WindowSettings
{
	bool fullscreen = false;
	int width = 1280;
	int height = 720;

    friend void from_json(const Json& json, WindowSettings& object)
    {
        WindowSettings defaultObject;

        FROM_JSON_WITH_DEFAULT(fullscreen);
        FROM_JSON_WITH_DEFAULT(width);
        FROM_JSON_WITH_DEFAULT(height);
    }

    friend void to_json(Json& json, const WindowSettings& object)
    {
        TO_JSON(fullscreen);
        TO_JSON(width);
        TO_JSON(height);
    }
};
