#pragma once

#include "GameHeader.h"

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
    void SetCameraPositionOffset(glm::vec3& offset) { this->_positionOffset = offset; }
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
    void SetYawPitch(float yaw, float pitch)
    {
        this->SetYaw(yaw);
        this->SetPitch(pitch);
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
    void AddYawPitch(float yaw, float pitch)
    {
        this->AddYaw(yaw);
        this->AddPitch(pitch);
    }

    void Temp(GLFWwindow* window)
    {
        float speed = 0.01f;

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            this->_cameraPosition += speed * this->_cameraDirection;

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            this->_cameraPosition -= speed * this->_cameraDirection;

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            this->_cameraPosition -= speed * glm::normalize(glm::cross(this->_cameraDirection, this->_cameraUp));

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            this->_cameraPosition += speed * glm::normalize(glm::cross(this->_cameraDirection, this->_cameraUp));

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            this->_cameraPosition += speed * this->_cameraUp;

        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
            this->_cameraPosition -= speed * this->_cameraUp;
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

