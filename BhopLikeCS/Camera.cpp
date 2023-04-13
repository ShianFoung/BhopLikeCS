#include "Camera.h"

Camera::Camera(float fov, float aspectRatio, float near, float far)
{
    this->_cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    this->_cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    this->_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    this->_positionOffset = glm::vec3(0.0f, 0.0f, 0.0f);
    this->_viewMatrix = glm::lookAt(this->_cameraPosition + this->_positionOffset, this->_cameraPosition + this->_positionOffset + this->_cameraDirection, this->_cameraUp);
    this->_projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, near, far);
    this->_yaw = -90.0f;
    this->_pitch = 0.0f;
}

Camera::~Camera()
{

}

// ===================================== Private =====================================

void Camera::_normalizeYaw()
{
    if (this->_yaw >= 360.0f || this->_yaw <= -360.0f)
        this->_yaw = glm::mod(this->_yaw, 360.0f);
}

void Camera::_normalizePitch()
{
    if (this->_pitch > 89.0f)
        this->_pitch = 89.0f;

    if (this->_pitch < -89.0f)
        this->_pitch = -89.0f;
}

void Camera::_updateCameraDirection()
{
    float radiansYaw = glm::radians(this->_yaw);
    float radiansPitch = glm::radians(this->_pitch);
    glm::vec3 direction {};

    direction.x = cos(radiansPitch) * cos(radiansYaw);
    direction.y = sin(radiansPitch);
    direction.z = cos(radiansPitch) * sin(radiansYaw);

    this->_cameraDirection = glm::normalize(direction);
}
