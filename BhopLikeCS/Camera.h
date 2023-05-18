#pragma once

#include "Header.h"

class Camera
{
public:
    Camera(float fov, float aspectRatio, float near = 7.0f, float far = 28400.0f);
    ~Camera();

    glm::mat4& GetProjectionMatrix();
    void GetViewSpaceVectors(glm::vec3* front, glm::vec3* right, glm::vec3* up);
    void GetCameraAngles(float* yaw, float* pitch);

    void SetPosition(glm::vec3& position);
    void SetPositionOffset(glm::vec3& offset);
    void SetEulerAngles(float yaw, float pitch);

    void AddEulerAngles(float yaw, float pitch);

    /*void Temp(GLFWwindow* window)
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
    }*/
private:
    float _yaw;
    float _pitch;
    glm::vec3 _position;
    glm::vec3 _direction;
    glm::vec3 _right;
    glm::vec3 _up;
    glm::vec3 _worldUp;
    glm::vec3 _positionOffset;
    glm::mat4 _modelViewMatrix;
    glm::mat4 _projectionMatrix;
    glm::mat4 _perspectiveMatrix;

    void _updateCameraVectors();
    void _updateProjectionMatrix();
};

