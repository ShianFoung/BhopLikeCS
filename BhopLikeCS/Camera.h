#pragma once

#include "GameHeader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>

#include <iostream>
#include <glm/gtx/string_cast.hpp>

class Camera
{
public:
    Camera(float fov, float aspectRatio, float near = 0.1f, float far = 1000.0f);
    ~Camera();

    glm::mat4& GetProjectionMatrix();
    glm::mat4& GetOrthogonalMatrix();

    void SetCameraPosition(glm::vec3& position);
    void SetCameraPositionOffset(glm::vec3& offset);
    void SetCameraAngles(float yaw, float pitch);

    void AddCameraAngles(float yaw, float pitch);

    void Temp(GLFWwindow* window)
    {
        float speed = 1.0f;

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

        this->_updateProjectionMatrix();
    }
private:
    float _yaw;
    float _pitch;
    glm::vec3 _cameraPosition;
    glm::vec3 _cameraDirection;
    glm::vec3 _cameraUp;
    glm::vec3 _cameraPositionOffset;
    glm::mat4 _modelViewMatrix;
    glm::mat4 _projectionMatrix;
    glm::mat4 _perspectiveMatrix;
    glm::mat4 _orthogonalMatrix;

    void _updateCameraDirection();
    void _updateProjectionMatrix();
};

