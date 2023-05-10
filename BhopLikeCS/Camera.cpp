#include "Camera.h"

Camera::Camera(float fov, float aspectRatio, float near, float far)
{
    this->_yaw = 90.0f;
    this->_pitch = 0.0f;
    // 相機預設的位置 (尚未對人物視野高度做偏移)
    this->_cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    // 相機朝向的位置
    this->_updateCameraDirection();
    // 相機上方面向的方向
    this->_cameraUp = glm::vec3(0.0f, 0.0f, 1.0f);
    // 因應人物視野的位置所做的偏移
    this->_cameraPositionOffset = glm::vec3(0.0f, 0.0f, 0.0f);
    this->_modelViewMatrix = glm::lookAt(this->_cameraPosition + this->_cameraPositionOffset,
                                         this->_cameraPosition + this->_cameraPositionOffset + this->_cameraDirection,
                                         this->_cameraUp);
    this->_perspectiveMatrix = glm::perspective(glm::radians(fov), aspectRatio, near, far);
    this->_orthogonalMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
    this->_projectionMatrix = this->_perspectiveMatrix * this->_modelViewMatrix;
}

Camera::~Camera() {  }

glm::mat4& Camera::GetProjectionMatrix()
{
    return this->_projectionMatrix;
}

glm::mat4& Camera::GetOrthogonalMatrix()
{
    return this->_orthogonalMatrix;
}

void Camera::SetCameraPosition(glm::vec3& position)
{
    this->_cameraPosition = position;

    this->_updateProjectionMatrix();
}

void Camera::SetCameraPositionOffset(glm::vec3& offset)
{
    this->_cameraPositionOffset = offset;

    this->_updateProjectionMatrix();
}

void Camera::SetCameraAngles(float yaw, float pitch)
{
    this->_yaw = yaw;
    this->_pitch = pitch;

    this->_updateCameraDirection();
    this->_updateProjectionMatrix();
}

void Camera::AddCameraAngles(float yaw, float pitch)
{
    this->_yaw += yaw;
    this->_pitch += pitch;

    this->_updateCameraDirection();
    this->_updateProjectionMatrix();
}

// ===================================== Private =====================================

void Camera::_updateCameraDirection()
{
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

    newDirection.x = cos(radiansPitch) * cos(radiansYaw);
    newDirection.y = -cos(radiansPitch) * sin(radiansYaw);
    newDirection.z = sin(radiansPitch);

    this->_cameraDirection = glm::normalize(newDirection);
}

void Camera::_updateProjectionMatrix()
{
    glm::vec3 cameraRealPosition = this->_cameraPosition + this->_cameraPositionOffset;
    this->_modelViewMatrix = glm::lookAt(cameraRealPosition,
                                         cameraRealPosition + this->_cameraDirection,
                                         this->_cameraUp);
    this->_projectionMatrix = this->_perspectiveMatrix * this->_modelViewMatrix;
}
