#pragma once

// ============================================
//                 ������Y��
// ============================================
// �ݭn�o�ӪF�誺��]�O�n�j�T�ת����C
// ���骺�sĶ�ɶ��A���M�]�t���禡�w�W�Ŧh�A
// �C���n�sĶ�ɪ�O���ɶ��u���Ӥ[�F�C
// ============================================

#define FROM_JSON_WITH_DEFAULT(name) object.name = json.value(#name, defaultObject.name)
#define TO_JSON(name) json[#name] = object.name

#define GLEW_STATIC
#define STB_IMAGE_STATIC
#define STBTT_STATIC
#define STB_IMAGE_IMPLEMENTATION

// ImGui �禡�w

// OpenGL �禡�w�A�ӥB�n�u���ɤJ glew�A���M�|����
#include <glew/glew.h>
#include <glfw/glfw3.h>

// C++ �зǨ禡�w
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

// Glm �禡�w
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

// Json �禡�w
#include <nlohmann/json.hpp>

using Json = nlohmann::ordered_json;

// STB �禡�w
#include <stb/stb_image.h>

// �ۤv���� Config �禡�w
#include "Config.h"

#include "Utils/Math.h"
#include "Utils/Collision.h"

namespace glm
{
    inline void to_json(Json& json, const glm::vec2& vector)
    {
        json = Json::array({ vector.x, vector.y });
    }

    inline void from_json(const Json& json, glm::vec2& vector)
    {
        vector.x = json[0];
        vector.y = json[1];
    }

    inline void to_json(Json& json, const glm::vec3& vector)
    {
        json = Json::array({ vector.x, vector.y, vector.z });
    }

    inline void from_json(const Json& json, glm::vec3& vector)
    {
        vector.x = json[0];
        vector.y = json[1];
        vector.z = json[2];
    }

    inline void to_json(Json& json, const glm::u8vec3& color)
    {
        json = Json::array({ color.r, color.g, color.b });
    }

    inline void from_json(const Json& json, glm::u8vec3& color)
    {
        color.r = json[0];
        color.g = json[1];
        color.b = json[2];
    }
}
