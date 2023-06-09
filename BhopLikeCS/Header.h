#pragma once

// ============================================
//                 ������Y��
// ============================================
// �ݭn�o�ӪF�誺��]�O�n�j�T�ת����C
// ���骺�sĶ�ɶ��A���M�]�t���禡�w�W�Ŧh�A
// �C���n�sĶ�ɪ�O���ɶ��u���Ӥ[�F�C
// �o��P�ɤ]�]�t�F�����ܼƸ�@�ǹ�Ϊ��\��A
// ���쥻�O�Q�n�� Utils �h�]�o�ǥ\��A
// ���G�̫�Q�@�Q�٬O��F�A���I�i�A�h���}�F �~�~�C
// ============================================

#define GLEW_STATIC
#define STB_IMAGE_STATIC
#define STBTT_STATIC
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION

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

using Json = nlohmann::json;

// STB �禡�w
#include <stb/stb_image.h>
#include <stb/stb_truetype.h>

// �ۤv���� Config �禡�w
#include "Config.h"

// ============================================
//                   �����ܼ�
// ============================================

// �����e�� (���P�C���ѪR�ת��e)
extern int g_WindowWidth;
// �������� (���P�C���ѪR�ת���)
extern int g_WindowHeight;
// �����O�_���ù�
extern bool g_WindowFullscrean;
// �ѪR�ת���� (�e���H��)
extern float g_ResolutionAspectRatio;
// �����e�ת��@�b
extern int g_WindowHalfWidth;
// �����e�ת��@�b (�B�I��)
extern float g_WindowHalfWidthFloat;
// �������ת��@�b
extern int g_WindowHalfHeight;
// �������ת��@�b (�B�I��)
extern float g_WindowHalfHeightFloat;

// ============================================
//                   �\��禡
// ============================================

// ���o�V�q���C�Ӥ��q�������
inline glm::vec3 AbsValues(const glm::vec3& vector)
{
    return glm::vec3(abs(vector.x), abs(vector.y), abs(vector.z));
}

// ���o������V�����ʳt��
inline float GetXYVelocity(const glm::vec3& velocity)
{
    return sqrt(velocity.x * velocity.x +
                velocity.y * velocity.y);
}

// ���o�T���Ŷ������ʳt��
inline float GetXYZVelocity(const glm::vec3& velocity)
{
    return sqrt(velocity.x * velocity.x +
                velocity.y * velocity.y +
                velocity.z * velocity.z);
}
