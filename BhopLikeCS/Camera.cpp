
#include "Header.h"

#include "Camera.h"

Camera::Camera(float fov, float aspectRatio, float near, float far)
{
    this->_yaw = 90.0f;
    this->_pitch = 0.0f;
    // 相機預設的位置 (尚未對人物視野高度做偏移)
    this->_position = glm::vec3(0.0f, 0.0f, 0.0f);
    // 相機上方所對應的世界向量 (相機上方所應指向的世界座標向量，假設根據下面的設定將 z 設成 -1.0f，那看到的東西就會反過來)
    this->_worldUp = glm::vec3(0.0f, 0.0f, 1.0f);
    // 依照上面的設定更新相機的所有所需向量
    this->_updateCameraVectors();
    // 因應人物眼睛的位置所做的偏移
    this->_positionOffset = glm::vec3(0.0f, 0.0f, 0.0f);
    this->_modelViewMatrix = glm::lookAt(this->_position + this->_positionOffset,
                                         this->_position + this->_positionOffset + this->_direction,
                                         this->_worldUp);
    // 計算投影矩陣 (near 與 far 是參考 CSGO 的設定)
    this->_perspectiveMatrix = glm::perspective(glm::radians(fov), aspectRatio, near, far);
    this->_projectionMatrix = this->_perspectiveMatrix * this->_modelViewMatrix;
}

Camera::~Camera() {  }

glm::mat4& Camera::GetProjectionMatrix() { return this->_projectionMatrix; }

void Camera::GetViewSpaceVectors(glm::vec3* front, glm::vec3* right, glm::vec3* up)
{
    if (front)
        *front = this->_direction;
    if (right)
        *right = this->_right;
    if (up)
        *up = this->_up;
}

void Camera::GetCameraAngles(float* yaw, float* pitch)
{
    if (yaw)
        *yaw = this->_yaw;
    if (pitch)
        *pitch = this->_pitch;
}

void Camera::SetPosition(glm::vec3& position)
{
    this->_position = position;

    this->_updateProjectionMatrix();
}

void Camera::SetPositionOffset(glm::vec3& offset)
{
    this->_positionOffset = offset;

    this->_updateProjectionMatrix();
}

void Camera::SetEulerAngles(float yaw, float pitch)
{
    this->_yaw = yaw;
    this->_pitch = pitch;

    this->_updateCameraVectors();
    this->_updateProjectionMatrix();
}

void Camera::AddEulerAngles(float yaw, float pitch)
{
    this->_yaw += yaw;
    this->_pitch += pitch;

    this->_updateCameraVectors();
    this->_updateProjectionMatrix();
}

// ===================================== Private =====================================

void Camera::_updateCameraVectors()
{
    // 限制 yaw 與 pitch 的範圍，不然無限增大會溢位
    if (this->_yaw > 180.0f)
        this->_yaw -= 360.0f;
    else if (this->_yaw <= -180.0f)
        this->_yaw += 360.0f;

    if (this->_pitch > 89.0f)
        this->_pitch = 89.0f;
    else if (this->_pitch < -89.0f)
        this->_pitch = -89.0f;

    float radiansYaw = glm::radians(this->_yaw);
    float radiansPitch = glm::radians(this->_pitch);
    glm::vec3 newDirection = {  };

    // 計算新的相機方向向量
    newDirection.x = cos(radiansPitch) * cos(radiansYaw);
    newDirection.y = cos(radiansPitch) * sin(radiansYaw);
    newDirection.z = sin(radiansPitch);
    this->_direction = glm::normalize(newDirection);

    // 計算新的相機右邊向量
    this->_right = glm::normalize(glm::cross(this->_direction, this->_worldUp));

    // 計算新的相機向上向量 (這個向上是實際的上方向量而不是 _worldUp 的固定向量)
    this->_up = glm::normalize(glm::cross(this->_right, this->_direction));
}

void Camera::_updateProjectionMatrix()
{
    glm::vec3 cameraRealPosition = this->_position + this->_positionOffset;
    this->_modelViewMatrix = glm::lookAt(cameraRealPosition,
                                         cameraRealPosition + this->_direction,
                                         this->_worldUp);
    this->_projectionMatrix = this->_perspectiveMatrix * this->_modelViewMatrix;
}
