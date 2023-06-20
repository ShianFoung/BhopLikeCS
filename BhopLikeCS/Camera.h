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
    // 相機水平角度
    float yaw;
    // 相機垂直角度
    float pitch;

    // 相機於世界座標的位置
    glm::vec3 position;
    // 相機面向方向
    glm::vec3 direction;
    // 相機上方朝向世界座標向量 (此值為固定值)
    glm::vec3 worldUp;
    // 相機右方向量
    glm::vec3 right;
    // 相機實際上方向量
    glm::vec3 up;

    // 透視投影矩陣
    glm::mat4 perspectiveMatrix;
    // 投影矩陣
    glm::mat4 projectionMatrix;

    inline void updateVectors();
    inline void updateProjectionMatrix();
};
