#pragma once

#include "../Json/IJsonObject.h"

struct WindowSettings final : IJsonObject
{
	bool fullscreen = false;
	int width = 1280;
	int height = 720;

	inline virtual void ToJson(Json& json) override
	{
		MEMBER_TO_JSON(fullscreen);
		MEMBER_TO_JSON(width);
		MEMBER_TO_JSON(height);
	}

	inline virtual void FromJson(Json& json) override
	{
		IF_JSON_NULL_CREATE_DEFAULT_VALUE;

		MEMBER_FROM_JSON(fullscreen);
		MEMBER_FROM_JSON(width);
		MEMBER_FROM_JSON(height);
	}
};
