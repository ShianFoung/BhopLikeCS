#pragma once

// ============================================
//                 全域標頭檔
// ============================================
// 需要這個東西的原因是要大幅度的降低
// 整體的編譯時間，不然包含的函式庫超級多，
// 每次要編譯時花費的時間真的太久了。
// ============================================

#define FROM_JSON_WITH_DEFAULT(name) object.name = json.value(#name, defaultObject.name)
#define TO_JSON(name) json[#name] = object.name

#define GLEW_STATIC
#define STB_IMAGE_STATIC
#define STBTT_STATIC
#define STB_IMAGE_IMPLEMENTATION

// ImGui 函式庫

// OpenGL 函式庫，而且要優先導入 glew，不然會報錯
#include <glew/glew.h>
#include <glfw/glfw3.h>

// C++ 標準函式庫
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>

// Glm 函式庫
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

// Json 函式庫
#include <nlohmann/json.hpp>

using Json = nlohmann::ordered_json;

// STB 函式庫
#include <stb/stb_image.h>

// 自己做的 Config 函式庫
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
