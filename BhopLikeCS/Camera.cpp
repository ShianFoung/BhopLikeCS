#include "../Header.h"

#include "Camera.h"

Camera::Camera(float fov, float aspectRatio, float near, float far)
{
    // �w�]�ݦV�� Y �b
    this->yaw = 90.0f;
    this->pitch = 0.0f;
    // �۾��w�]����m (�|����H���������װ�����)
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
    // �۾��W��ҹ������@�ɦV�q (�۾��W��������V���@�ɮy�ЦV�q�A���]�ھڤU�����]�w�N z �]�� -1.0f�A���ݨ쪺�F��N�|�ϹL��)
    this->worldUp = glm::vec3(0.0f, 0.0f, 1.0f);
    // �p��z����v�x�} (near �P far �O�Ѧ� CSGO ���]�w)
    this->perspectiveMatrix = glm::perspective(glm::radians(fov), aspectRatio, near, far);

    // �̷ӤW�����]�w��s�۾����Ҧ��Ѽ�
    this->Update();
}

void Camera::GetViewAngles(float* viewAngles)
{
    viewAngles[0] = this->yaw;
    viewAngles[1] = this->pitch;
    viewAngles[2] = 0.0f;
}

glm::vec3& Camera::GetFrontVector()
{
    return this->direction;
}

glm::vec3& Camera::GetRightVector()
{
    return this->right;
}

glm::vec3& Camera::GetUpVector()
{
    return this->up;
}

glm::mat4& Camera::GetProjectionMatrix()
{
    return this->projectionMatrix;
}

void Camera::SetPosition(const glm::vec3& position)
{
    this->position = position;
}

void Camera::SetViewAngles(const float yaw, const float pitch)
{
    this->yaw = yaw;
    this->pitch = pitch;
}

void Camera::AddViewAngles(const float yaw, const float pitch)
{
    this->yaw += yaw;
    this->pitch += pitch;
}

void Camera::Update()
{
    this->updateVectors();
    this->updateProjectionMatrix();
}

inline void Camera::updateVectors()
{
    // ���� yaw ���d��A���M�L���W�j�|����
    if (this->yaw > 180.0f)
        this->yaw -= 360.0f;
    else if (this->yaw <= -180.0f)
        this->yaw += 360.0f;

    // ���� pitch ���d��A����ݨ� +-90 �סA���M�|�o�͸U�V�� (Gimbal Lock)
    if (this->pitch > 89.0f)
        this->pitch = 89.0f;
    else if (this->pitch < -89.0f)
        this->pitch = -89.0f;

    // ����|�סA�U���N���Τ@�����ഫ�A�٭p��ɶ�
    float radiansYaw = glm::radians(this->yaw);
    float radiansPitch = glm::radians(this->pitch);

    // �p��s���۾���V�V�q
    glm::vec3 newDirection {  };
    newDirection.x = cos(radiansPitch) * cos(radiansYaw);
    newDirection.y = cos(radiansPitch) * sin(radiansYaw);
    newDirection.z = sin(radiansPitch);
    this->direction = glm::normalize(newDirection);

    // �p��s���۾��k��V�q
    this->right = glm::normalize(glm::cross(this->direction, this->worldUp));

    // �p��s���۾��V�W�V�q (�o�ӦV�W�O��ڪ��W��V�q�Ӥ��O worldUp ���T�w�V�q)
    this->up = glm::normalize(glm::cross(this->right, this->direction));
}

inline void Camera::updateProjectionMatrix()
{
    this->projectionMatrix = this->perspectiveMatrix * glm::lookAt(this->position,
                                                                   this->position + this->direction,
                                                                   this->worldUp);
}
