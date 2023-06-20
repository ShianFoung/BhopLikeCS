#pragma once

#include "Camera.h"

enum PlayerButtons : int
{
    FRONT = (1 << 0),
    BACK = (1 << 1),
    LEFT = (1 << 2),
    RIGHT = (1 << 3),
    JUMP = (1 << 4),
    DUCK = (1 << 5),
    YAWLEFT = (1 << 6),
    YAWRIGHT = (1 << 7)
};

enum PlayerStates : int
{
    NOCLIPMODE = (1 << 0),
    ONGROUND = (1 << 1)
};

class Player
{
public:
    Player(const float fov, const int windowWidth, const int windowHeight);

    Camera& GetCamera();
    glm::vec3& GetPosition();
    glm::vec3& GetVelocity();
    int GetPreviousButtons();
    int GetButtons();
    int GetStates();

    void SetSensitivity(const float sensitivity);
    void SetPosition(const glm::vec3& position);
    void SetVelocity(const glm::vec3& velocity);

    void AddStates(int states);

    void RemoveStates(int states);

    bool IsKeyPressed(int button);

    void HandleInputs(GLFWwindow* window, float frameTime);
    void Update(float frameTime);
private:
    inline static const float StandingHeight = 72.0f;
    inline static const float CrouchingHeight = 54.0f;
    inline static const float StandingEyeLevel = 64.0f;
    inline static const float CrouchingEyeLevel = 46.0f;

    const float windowHalfWidth;
    const float windowHalfHeight;

    Camera camera;

    glm::vec3 position;
    glm::vec3 velocity;

    bool isFirstMove;
    float sensitivity;
    int previousButtons;
    int buttons;
    int states;

    void keyInput(GLFWwindow* window);
    void mouseInput(GLFWwindow* window, float frameTime);

    inline void setButton(GLFWwindow* window, int key, PlayerButtons button);
};
