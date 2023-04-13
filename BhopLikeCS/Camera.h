#pragma once

#include "GLHeader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>

enum CameraDirection
{
    POSITIVE_X,
    NEGATIVE_X,
    POSITIVE_Z,
    NEGATIVE_Z
};

class Camera
{
public:
    Camera(float fov, float aspectRatio, float near = 0.1f, float far = 1000.0f);
    ~Camera();

    glm::vec3 GetCameraPosition() { return this->_cameraPosition; }
    glm::mat4 GetViewProjectionMatrix()
    {
        this->_updateCameraDirection();
        this->_viewMatrix = glm::lookAt(this->_cameraPosition + this->_positionOffset, this->_cameraPosition + this->_positionOffset + this->_cameraDirection, this->_cameraUp);
        return this->_projectionMatrix * this->_viewMatrix;
    }

    void SetCameraPosition(glm::vec3& position) { this->_cameraPosition = position; }
    void SetCameraDirection(CameraDirection direction)
    {
        switch (direction)
        {
            case POSITIVE_X:
                this->_cameraDirection = glm::vec3(1.0f, 0.0f, 0.0f);
                this->_yaw = 0.0f;
                break;
            case NEGATIVE_X:
                this->_cameraDirection = glm::vec3(-1.0f, 0.0f, 0.0f);
                this->_yaw = 180.0f;
                break;
            case POSITIVE_Z:
                this->_cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
                this->_yaw = -90.0f;
                break;
            case NEGATIVE_Z:
                this->_cameraDirection = glm::vec3(0.0f, 0.0f, 1.0f);
                this->_yaw = 90.0f;
                break;
        }

        this->_pitch = 0.0f;
    }
    void SetYaw(float yaw)
    {
        this->_yaw = yaw;
        this->_normalizeYaw();
    }
    void SetPitch(float pitch)
    {
        this->_pitch = pitch;
        this->_normalizePitch();
    }

    void AddYaw(float yaw)
    {
        this->_yaw += yaw;
        this->_normalizeYaw();
    }
    void AddPitch(float pitch)
    {
        this->_pitch += pitch;
        this->_normalizePitch();
    }

private:
    glm::vec3 _cameraPosition;
    glm::vec3 _cameraDirection;
    glm::vec3 _cameraUp;
    glm::vec3 _positionOffset;
    glm::mat4 _viewMatrix;
    glm::mat4 _projectionMatrix;
    float _yaw;
    float _pitch;

    void _normalizeYaw();
    void _normalizePitch();
    void _updateCameraDirection();
};

//class Camera
//{
//public:
//    Camera(float fov, float aspectRatio, float near, float far);
//    ~Camera();
//
//    const float GetYaw() { return this->_yaw; }
//    const float GetPitch() { return this->_pitch; }
//    const glm::vec3& GetCameraPosition() { return this->_cameraPosition; }
//    const glm::vec3& GetCameraDirection() { return this->_cameraDirection; }
//    const glm::vec3& GetCameraUp() { return this->_cameraUp; }
//    const glm::mat4& GetProjectionViewMatrix() { return this->_projectionMatrix * this->_viewMatrix; }
//
//    void SetSensitivity(float sensitivity) { this->_sensitivity = sensitivity; }
//    void SetYaw(float yaw) { this->_yaw = yaw; }
//    void SetPitch(float pitch) { this->_pitch = pitch; }
//    void SetYawPitch(float yaw, float pitch) { this->SetYaw(yaw); this->SetPitch(pitch); }
//    void SetCameraPosition(glm::vec3 &position);
//    void SetCameraDirection(glm::vec3 &direction);
//    void SetCameraUp(glm::vec3 &up);
//
//    void RecalculateMatrix();
//
//    void MouseInput(double xPos, double yPos);
//    void KeyInput(GLFWwindow* window);
//private:
//    const glm::mat4 _identityModelMatrix = glm::mat4(1.0f);
//
//    float _fov;
//    float _aspectRatio;
//    float _near;
//    float _far;
//
//    float _sensitivity = 1.0f;
//    float _yaw = -90.0f;
//    float _pitch = 0.0f;
//    bool _firstclick = true;
//
//    glm::vec3 _cameraPosition;
//    glm::vec3 _cameraDirection;
//    glm::vec3 _cameraUp;
//
//    glm::mat4 _viewMatrix;
//    glm::mat4 _projectionMatrix;
//};
