#pragma once

#include "../Header.h"

#include "../Data/BoundingBox.h"

namespace utils
{
    // 考慮時間性的 AABB 碰撞檢測
    // 需傳入玩家與欲偵測物件的 BoundingBox 與玩家當前的速度 (必須乘以 frameTime 後的)
    // 回傳:
    // - return: 玩家移動的時間，介於 0.0f ~ 1.0f。(假設回傳 0.2f，代表只花了 0.2 的單位時間就撞到物件了)
    // - outNormal: 玩家如果有撞到物體 (return 數值小於 1.0)，回傳撞擊表面方向。
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
