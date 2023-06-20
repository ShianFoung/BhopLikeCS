#pragma once

#include "../Header.h"

namespace utils
{
    inline float GetXYVectorLength(const glm::vec3& vector)
    {
        return std::sqrtf(vector.x * vector.x +
                          vector.y * vector.y);
    }

    // ���o�V�q���C�Ӥ��q�������
    inline constexpr glm::vec3 AbsVectors(const glm::vec3& vector)
    {
        return glm::vec3(abs(vector.x), abs(vector.y), abs(vector.z));
    }

    inline constexpr float GetVectorLengthSqr(const glm::vec3& vector)
    {
        return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;
    }

    // �S��γ~�A�p�G�ϥ� glm::normalize ���ܡA���׬� 0 �|�ɭP vector ���ƭ��ܦ��L���j
    // �ҥH�� CS ��l�X���Ѫ���k
    inline float GetVectorLengthAndNormalize(glm::vec3& vector)
    {
        float length = glm::length(vector);
        float inverseLength = 1.0f / (length + FLT_EPSILON);

        vector *= inverseLength;

        return length;
    }
}
