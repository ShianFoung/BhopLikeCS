#pragma once

#include "../Header.h"

#define MEMBER_TO_JSON(name) json[#name] = this->name
#define MEMBER_FROM_JSON(name) this->name = json.value(#name, name)
#define IF_JSON_NULL_CREATE_DEFAULT_VALUE \
	if (json == nullptr) \
		this->ToJson(json)

struct IJsonObject
{
	inline virtual void ToJson(Json& json) = 0;
	inline virtual void FromJson(Json& json) = 0;
};
