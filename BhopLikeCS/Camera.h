#pragma once

#include "GLHeader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>

class Camera
{
public:
    Camera(float fov, float aspectRatio, float near, float far);
    ~Camera();

    const float GetYaw() { return this->_yaw; }
    const float GetPitch() { return this->_pitch; }
    const glm::vec3& GetCameraPosition() { return this->_cameraPosition; }
    const glm::vec3& GetCameraDirection() { return this->_cameraDirection; }
    const glm::vec3& GetCameraUp() { return this->_cameraUp; }
    const glm::mat4& GetProjectionViewMatrix() { return this->_projectionMatrix * this->_viewMatrix; }

    void SetSensitivity(float sensitivity) { this->_sensitivity = sensitivity; }
    void SetYaw(float yaw) { this->_yaw = yaw; }
    void SetPitch(float pitch) { this->_pitch = pitch; }
    void SetYawPitch(float yaw, float pitch) { this->SetYaw(yaw); this->SetPitch(pitch); }
    void SetCameraPosition(glm::vec3 &position);
    void SetCameraDirection(glm::vec3 &direction);
    void SetCameraUp(glm::vec3 &up);

    void RecalculateMatrix();

    void MouseInput(double xPos, double yPos);
    void KeyInput(GLFWwindow* window);
private:
    const glm::mat4 _identityModelMatrix = glm::mat4(1.0f);

    float _fov;
    float _aspectRatio;
    float _near;
    float _far;

    float _sensitivity = 1.0f;
    float _yaw = -90.0f;
    float _pitch = 0.0f;
    bool _firstclick = true;

    glm::vec3 _cameraPosition;
    glm::vec3 _cameraDirection;
    glm::vec3 _cameraUp;

    glm::mat4 _viewMatrix;
    glm::mat4 _projectionMatrix;
};
