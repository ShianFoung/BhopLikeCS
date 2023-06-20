#pragma once

#include "../Header.h"

struct ConsoleSettings
{
	bool openConsole = true;
	int xPosition = 10;
	int yPosition = 10;

    friend void from_json(const Json& json, ConsoleSettings& object)
    {
        ConsoleSettings defaultObject;

        FROM_JSON_WITH_DEFAULT(openConsole);
        FROM_JSON_WITH_DEFAULT(xPosition);
        FROM_JSON_WITH_DEFAULT(yPosition);
    }

    friend void to_json(Json& json, const ConsoleSettings& object)
    {
        TO_JSON(openConsole);
        TO_JSON(xPosition);
        TO_JSON(yPosition);
    }
};
