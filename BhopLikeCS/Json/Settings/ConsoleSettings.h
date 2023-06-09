#pragma once

#include "../Json/IJsonObject.h"

struct ConsoleSettings : public IJsonObject
{
	bool openConsole = true;
	int xPosition = 10;
	int yPosition = 10;

	inline virtual void ToJson(Json& json) override
	{
		MEMBER_TO_JSON(openConsole);
		MEMBER_TO_JSON(xPosition);
		MEMBER_TO_JSON(yPosition);
	}

	inline virtual void FromJson(Json& json) override
	{
		IF_JSON_NULL_CREATE_DEFAULT_VALUE;

		MEMBER_FROM_JSON(openConsole);
		MEMBER_FROM_JSON(xPosition);
		MEMBER_FROM_JSON(yPosition);
	}
};
