#pragma once

#include "../Header.h"

namespace utils
{
    inline float GetXYVectorLength(const glm::vec3& vector)
    {
        return std::sqrtf(vector.x * vector.x +
                          vector.y * vector.y);
    }

    // 取得向量中每個分量的絕對值
    inline constexpr glm::vec3 AbsVectors(const glm::vec3& vector)
    {
        return glm::vec3(abs(vector.x), abs(vector.y), abs(vector.z));
    }

    inline constexpr float GetVectorLengthSqr(const glm::vec3& vector)
    {
        return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
    }

    // 特殊用途，如果使用 glm::normalize 的話，長度為 0 會導致 vector 的數值變成無限大
    // 所以用 CS 原始碼提供的方法
    inline float GetVectorLengthAndNormalize(glm::vec3& vector)
    {
        float length = glm::length(vector);
        float inverseLength = 1.0f / (length + FLT_EPSILON);

        vector *= inverseLength;

        return length;
    }
}
