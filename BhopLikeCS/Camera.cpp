#include "Camera.h"

Camera::Camera(float fov, float aspectRatio, float near, float far)
{
    this->_fov = fov;
    this->_aspectRatio = aspectRatio;
    this->_near = near;
    this->_far = far;

    // 相機的位置
    this->_cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    // 相機看向的位置
    this->_cameraDirection = glm::vec3(0.0f, 0.0f, -1.0f);
    // IDK... 學到再補
    this->_cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
    
    this->_viewMatrix = glm::lookAt(this->_cameraPosition, this->_cameraPosition + this->_cameraDirection, this->_cameraUp);
    this->_projectionMatrix = glm::perspective(glm::radians(this->_fov), this->_aspectRatio, this->_near, this->_far);
}

Camera::~Camera() {  }

void Camera::SetCameraPosition(glm::vec3& position)
{
    this->_cameraPosition = position;

    this->RecalculateMatrix();
}

void Camera::SetCameraDirection(glm::vec3& direction)
{
    this->_cameraDirection = direction;

    this->RecalculateMatrix();
}

void Camera::SetCameraUp(glm::vec3& up)
{
    this->_cameraUp = up;

    this->RecalculateMatrix();
}

void Camera::RecalculateMatrix()
{
    this->_viewMatrix = glm::lookAt(this->_cameraPosition, this->_cameraPosition + this->_cameraDirection, this->_cameraUp);
}

void Camera::MouseInput(double xPos, double yPos)
{
    
}

void Camera::KeyInput(GLFWwindow* window)
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

    /*if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        if (this->_firstclick)
        {
            glfwSetCursorPos(window, (1280.0f / 2), (720.0f / 2));
            this->_firstclick = false;
        }

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float rotX = 20.0f * (float) (mouseX - (1280.0f / 2)) / 1280.0f;
        float rotY = 20.0f * (float) (mouseY - (720.0f / 2)) / 720.0f;

        glm::vec3 newDirection = glm::rotate(this->_cameraDirection, glm::radians(-rotY), glm::normalize(glm::cross(this->_cameraDirection, this->_cameraUp)));

        if (!((glm::angle(newDirection, this->_cameraUp) <= glm::radians(5.0f)) || (glm::angle(newDirection, -this->_cameraUp) <= glm::radians(5.0f))))
        {
            this->_cameraDirection = newDirection;
        }

        this->_cameraDirection = glm::rotate(this->_cameraDirection, glm::radians(-rotX), this->_cameraUp);

        glfwSetCursorPos(window, (1280.0f / 2), (720.0f / 2));
    }*/

    this->RecalculateMatrix();
}