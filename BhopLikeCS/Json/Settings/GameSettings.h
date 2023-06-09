#pragma once

#include "../Json/IJsonObject.h"

struct GameSettings final : public IJsonObject
{
	int tickrateAndFps = 128;

	inline virtual void ToJson(Json& json) override
	{
		MEMBER_TO_JSON(tickrateAndFps);
	}

	inline virtual void FromJson(Json& json) override
	{
		IF_JSON_NULL_CREATE_DEFAULT_VALUE;

		MEMBER_FROM_JSON(tickrateAndFps);
	}
};