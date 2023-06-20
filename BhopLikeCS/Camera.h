#pragma once

class Camera final
{
public:
    Camera(float fov, float aspectRatio, float near = 7.0f, float far = 28400.0f);

    void GetViewAngles(float* viewAngles);
    glm::vec3& GetFrontVector();
    glm::vec3& GetRightVector();
    glm::vec3& GetUpVector();
    glm::mat4& GetProjectionMatrix();

    void SetPosition(const glm::vec3& position);
    void SetViewAngles(const float yaw = 0.0f, const float pitch = 0.0f);

    void AddViewAngles(const float yaw = 0.0f, const float pitch = 0.0f);

    void Update();
private:
    // �۾���������
    float yaw;
    // �۾���������
    float pitch;

    // �۾���@�ɮy�Ъ���m
    glm::vec3 position;
    // �۾����V��V
    glm::vec3 direction;
    // �۾��W��¦V�@�ɮy�ЦV�q (���Ȭ��T�w��)
    glm::vec3 worldUp;
    // �۾��k��V�q
    glm::vec3 right;
    // �۾���ڤW��V�q
    glm::vec3 up;

    // �z����v�x�}
    glm::mat4 perspectiveMatrix;
    // ��v�x�}
    glm::mat4 projectionMatrix;

    inline void updateVectors();
    inline void updateProjectionMatrix();
};
