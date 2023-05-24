#pragma once

#define _CRT_SECURE_NO_WARNINGS

// OpenGL 函式庫，而且要優先導入 glew，不然會報錯
#include <glew/glew.h>
#include <glfw/glfw3.h>

// C++ 標準函式庫
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Glm 函式庫
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

// Json 函式庫
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// STB 函式庫
#define STB_IMAGE_STATIC
#define STBTT_STATIC
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stb/stb_truetype.h>

// 自己做的 Config 函式庫
#include "Config.h"

// ============================================
//                   全域變數
// ============================================

// 視窗寬度 (等同遊戲解析度的寬)
static int g_WindowWidth;
// 視窗高度 (等同遊戲解析度的高)
static int g_WindowHeight;
// 解析度的比值 (寬除以高)
static float g_ResolutionAspectRatio;
// 視窗寬度的一半
static int g_WindowHalfWidth;
// 視窗高度的一半
static int g_WindowHalfHeight;

// ============================================
//                   功能函式
// ============================================

// 取向量中每個分量的絕對值
inline glm::vec3 AbsValues(const glm::vec3& vector)
{
    return glm::vec3(abs(vector.x), abs(vector.y), abs(vector.z));
}
