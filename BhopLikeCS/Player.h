#pragma once

#include "Header.h"

#include "Camera.h"

#define KEY_HANDLE(window, key, buttons, buttonType) \
	if (glfwGetKey(window, key) == GLFW_PRESS) \
		buttons |= buttonType; \
	else \
		buttons &= ~buttonType;

static float cl_yawspeed = 210.0f;

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

class Player
{
public:
	Player(float fov, float windowWidth, float windowHeight);
	~Player();

	glm::vec3& GetPosition();
	glm::vec3& GetVelocity();
	glm::vec3& GetViewAngles();
	Camera& GetCamera();
	int GetButtons();

	void SetPosition(glm::vec3& newPosition);
	void SetVelocity(glm::vec3& newVelocity);

	bool IsNoclip();
	bool IsPressedKey(int buttons);

	void ClearVelocity();

	void HandleInputs(GLFWwindow* window, float deltaTime);
	void CreateMove();
	void Update();
private:
	Camera _camera;
	glm::vec3 _lastPosition;
	glm::vec3 _position;
	glm::vec3 _velocity;
	glm::vec3 _lastViewAngles;
	glm::vec3 _viewAngles;
	float _windowWidth;
	float _windowHeight;
	float _windowCenterX;
	float _windowCenterY;

	bool _isNoclip = true;
	bool _isFirstMove = true;
	float _sensitivity = 3.0f;
	int _lastButtons = 0;
	int _buttons = 0;

	void _keyInput(GLFWwindow* window);
	void _mouseInput(GLFWwindow* window, float deltaTime);
};

////    const glm::vec3 _normalBBox = glm::vec3(32.0f, 72.0f, 32.0f);
////    const glm::vec3 _crouchBBox = glm::vec3(32.0f, 54.0f, 32.0f);
////    const float normalEyeLevel = 64.0f;
////    const float crouchEyeLevel = 46.0f;
