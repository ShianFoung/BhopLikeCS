
#include "Header.h"

#include "Camera.h"

Camera::Camera(float fov, float aspectRatio, float near, float far)
{
    this->_yaw = 90.0f;
    this->_pitch = 0.0f;
    // �۾��w�]����m (�|����H���������װ�����)
    this->_position = glm::vec3(0.0f, 0.0f, 0.0f);
    // �۾��W��ҹ������@�ɦV�q (�۾��W��������V���@�ɮy�ЦV�q�A���]�ھڤU�����]�w�N z �]�� -1.0f�A���ݨ쪺�F��N�|�ϹL��)
    this->_worldUp = glm::vec3(0.0f, 0.0f, 1.0f);
    // �̷ӤW�����]�w��s�۾����Ҧ��һݦV�q
    this->_updateCameraVectors();
    // �]���H����������m�Ұ�������
    this->_positionOffset = glm::vec3(0.0f, 0.0f, 0.0f);
    this->_modelViewMatrix = glm::lookAt(this->_position + this->_positionOffset,
                                         this->_position + this->_positionOffset + this->_direction,
                                         this->_worldUp);
    // �p���v�x�} (near �P far �O�Ѧ� CSGO ���]�w)
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
    // ���� yaw �P pitch ���d��A���M�L���W�j�|����
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

    // �p��s���۾���V�V�q
    newDirection.x = cos(radiansPitch) * cos(radiansYaw);
    newDirection.y = cos(radiansPitch) * sin(radiansYaw);
    newDirection.z = sin(radiansPitch);
    this->_direction = glm::normalize(newDirection);

    // �p��s���۾��k��V�q
    this->_right = glm::normalize(glm::cross(this->_direction, this->_worldUp));

    // �p��s���۾��V�W�V�q (�o�ӦV�W�O��ڪ��W��V�q�Ӥ��O _worldUp ���T�w�V�q)
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
