#pragma once

#define _CRT_SECURE_NO_WARNINGS

// OpenGL �禡�w�A�ӥB�n�u���ɤJ glew�A���M�|����
#include <glew/glew.h>
#include <glfw/glfw3.h>

// C++ �зǨ禡�w
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Glm �禡�w
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

// Json �禡�w
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// STB �禡�w
#define STB_IMAGE_STATIC
#define STBTT_STATIC
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <stb/stb_truetype.h>

// �ۤv���� Config �禡�w
#include "Config.h"

// ============================================
//                   �����ܼ�
// ============================================

// �����e�� (���P�C���ѪR�ת��e)
static int g_WindowWidth;
// �������� (���P�C���ѪR�ת���)
static int g_WindowHeight;
// �ѪR�ת���� (�e���H��)
static float g_ResolutionAspectRatio;
// �����e�ת��@�b
static int g_WindowHalfWidth;
// �������ת��@�b
static int g_WindowHalfHeight;

// ============================================
//                   �\��禡
// ============================================

// ���V�q���C�Ӥ��q�������
inline glm::vec3 AbsValues(const glm::vec3& vector)
{
    return glm::vec3(abs(vector.x), abs(vector.y), abs(vector.z));
}
