#pragma once

// ============================================
//                 全域標頭檔
// ============================================
// 需要這個東西的原因是要大幅度的降低
// 整體的編譯時間，不然包含的函式庫超級多，
// 每次要編譯時花費的時間真的太久了。
// 這邊同時也包含了全域變數跟一些實用的功能，
// 其實原本是想要用 Utils 去包這些功能，
// 結果最後想一想還是算了，有點懶再去分開了 ㄏㄏ。
// ============================================

#define GLEW_STATIC
#define STB_IMAGE_STATIC
#define STBTT_STATIC
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

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

using Json = nlohmann::json;

// STB 函式庫
#include <stb/stb_image.h>
#include <stb/stb_truetype.h>

// 自己做的 Config 函式庫
#include "Config.h"

// ============================================
//                   全域變數
// ============================================

// 視窗寬度 (等同遊戲解析度的寬)
extern int g_WindowWidth;
// 視窗高度 (等同遊戲解析度的高)
extern int g_WindowHeight;
// 視窗是否全螢幕
extern bool g_WindowFullscrean;
// 解析度的比值 (寬除以高)
extern float g_ResolutionAspectRatio;
// 視窗寬度的一半
extern int g_WindowHalfWidth;
// 視窗寬度的一半 (浮點數)
extern float g_WindowHalfWidthFloat;
// 視窗高度的一半
extern int g_WindowHalfHeight;
// 視窗高度的一半 (浮點數)
extern float g_WindowHalfHeightFloat;

// ============================================
//                   功能函式
// ============================================

// 取得向量中每個分量的絕對值
inline glm::vec3 AbsValues(const glm::vec3& vector)
{
    return glm::vec3(abs(vector.x), abs(vector.y), abs(vector.z));
}

// 取得水平方向的移動速度
inline float GetXYVelocity(const glm::vec3& velocity)
{
    return sqrt(velocity.x * velocity.x +
                velocity.y * velocity.y);
}

// 取得三維空間的移動速度
inline float GetXYZVelocity(const glm::vec3& velocity)
{
    return sqrt(velocity.x * velocity.x +
                velocity.y * velocity.y +
                velocity.z * velocity.z);
}
