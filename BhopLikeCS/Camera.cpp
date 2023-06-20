#include "../Header.h"

#include "Camera.h"

Camera::Camera(float fov, float aspectRatio, float near, float far)
{
    // 預設看向正 Y 軸
    this->yaw = 90.0f;
    this->pitch = 0.0f;
    // 相機預設的位置 (尚未對人物視野高度做偏移)
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
    // 相機上方所對應的世界向量 (相機上方所應指向的世界座標向量，假設根據下面的設定將 z 設成 -1.0f，那看到的東西就會反過來)
    this->worldUp = glm::vec3(0.0f, 0.0f, 1.0f);
    // 計算透視投影矩陣 (near 與 far 是參考 CSGO 的設定)
    this->perspectiveMatrix = glm::perspective(glm::radians(fov), aspectRatio, near, far);

    // 依照上面的設定更新相機的所有參數
    this->Update();
}

void Camera::GetViewAngles(float* viewAngles)
{
    viewAngles[0] = this->yaw;
    viewAngles[1] = this->pitch;
    viewAngles[2] = 0.0f;
}

glm::vec3& Camera::GetFrontVector()
{
    return this->direction;
}

glm::vec3& Camera::GetRightVector()
{
    return this->right;
}

glm::vec3& Camera::GetUpVector()
{
    return this->up;
}

glm::mat4& Camera::GetProjectionMatrix()
{
    return this->projectionMatrix;
}

void Camera::SetPosition(const glm::vec3& position)
{
    this->position = position;
}

void Camera::SetViewAngles(const float yaw, const float pitch)
{
    this->yaw = yaw;
    this->pitch = pitch;
}

void Camera::AddViewAngles(const float yaw, const float pitch)
{
    this->yaw += yaw;
    this->pitch += pitch;
}

void Camera::Update()
{
    this->updateVectors();
    this->updateProjectionMatrix();
}

inline void Camera::updateVectors()
{
    // 限制 yaw 的範圍，不然無限增大會溢位
    if (this->yaw > 180.0f)
        this->yaw -= 360.0f;
    else if (this->yaw <= -180.0f)
        this->yaw += 360.0f;

    // 限制 pitch 的範圍，不能看到 +-90 度，不然會發生萬向鎖 (Gimbal Lock)
    if (this->pitch > 89.0f)
        this->pitch = 89.0f;
    else if (this->pitch < -89.0f)
        this->pitch = -89.0f;

    // 先轉徑度，下面就不用一直做轉換，省計算時間
    float radiansYaw = glm::radians(this->yaw);
    float radiansPitch = glm::radians(this->pitch);

    // 計算新的相機方向向量
    glm::vec3 newDirection {  };
    newDirection.x = cos(radiansPitch) * cos(radiansYaw);
    newDirection.y = cos(radiansPitch) * sin(radiansYaw);
    newDirection.z = sin(radiansPitch);
    this->direction = glm::normalize(newDirection);

    // 計算新的相機右邊向量
    this->right = glm::normalize(glm::cross(this->direction, this->worldUp));

    // 計算新的相機向上向量 (這個向上是實際的上方向量而不是 worldUp 的固定向量)
    this->up = glm::normalize(glm::cross(this->right, this->direction));
}

inline void Camera::updateProjectionMatrix()
{
    this->projectionMatrix = this->perspectiveMatrix * glm::lookAt(this->position,
                                                                   this->position + this->direction,
                                                                   this->worldUp);
}
