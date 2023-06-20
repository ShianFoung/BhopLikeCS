#pragma once

#include "../Header.h"

#include "../Data/BoundingBox.h"

namespace utils
{
    // �Ҽ{�ɶ��ʪ� AABB �I���˴�
    // �ݶǤJ���a�P���������� BoundingBox �P���a��e���t�� (�������H frameTime �᪺)
    // �^��:
    // - return: ���a���ʪ��ɶ��A���� 0.0f ~ 1.0f�C(���]�^�� 0.2f�A�N��u��F 0.2 �����ɶ��N���쪫��F)
    // - outNormal: ���a�p�G�����쪫�� (return �ƭȤp�� 1.0)�A�^�Ǽ�������V�C
    inline float SweptAABB(const BoundingBox& player, const glm::vec3& velocity, const BoundingBox& object, glm::vec3& outNormal)
    {
        glm::vec3 entry, exit;
        glm::vec3 dEntry, dExit;
        glm::vec3 absVelocity = utils::AbsVectors(velocity);

        for (int i = 0; i < 3; i++)
        {
            if (velocity[i] == 0.0f)
            {
                if (player.min[i] < object.max[i] && object.min[i] < player.max[i])
                {
                    entry[i] = -std::numeric_limits<float>::infinity();
                    exit[i] = std::numeric_limits<float>::infinity();
                }
                else
                    return 1.0f;
            }
            else
            {
                if (velocity[i] > 0.0f)
                {
                    dEntry[i] = object.min[i] - player.max[i];
                    dExit[i] = object.max[i] - player.min[i];
                }
                else
                {
                    dEntry[i] = player.min[i] - object.max[i];
                    dExit[i] = player.max[i] - object.min[i];
                }

                entry[i] = dEntry[i] / absVelocity[i];
                exit[i] = dExit[i] / absVelocity[i];
            }
        }

        if (entry.x > exit.y || entry.y > exit.x ||
            entry.y > exit.z || entry.z > exit.y ||
            entry.z > exit.x || entry.x > exit.z)
        {
            return 1.0f;
        }

        float entryTime = entry.x;

        for (int i = 1; i < 3; i++)
            if (entryTime < entry[i])
                entryTime = entry[i];

        if (entryTime < 0.0f || entryTime > 1.0f)
        {
            return 1.0f;
        }

        outNormal.x = outNormal.y = outNormal.z = 0.0f;

        if (entry.x > entry.y && entry.x > entry.z)
        {
            outNormal.x = velocity.x < 0.0f ? 1.0f : -1.0f;
        }
        else if (entry.y > entry.x && entry.y > entry.z)
        {
            outNormal.y = velocity.y < 0.0f ? 1.0f : -1.0f;
        }
        else
        {
            outNormal.z = velocity.z < 0.0f ? 1.0f : -1.0f;
        }

        return entryTime;
    }
}
