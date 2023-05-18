#include "Player.h"

Player::Player(float fov, float windowWidth, float windowHeight)
	: _camera(fov, windowWidth / windowHeight)
{
	this->_lastPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	this->_position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->_viewAngles = glm::vec3(0.0f, 0.0f, 0.0f);
	this->_lastViewAngles = glm::vec3(0.0f, 0.0f, 0.0f);
	this->_windowWidth = windowWidth;
	this->_windowHeight = windowHeight;
	this->_windowCenterX = this->_windowWidth / 2.0f;
	this->_windowCenterY = this->_windowHeight / 2.0f;

	glm::vec3 cameraOffset = glm::vec3(0.0f, 0.0f, 64.0f);

	this->_camera.SetPositionOffset(cameraOffset);
}
Player::~Player() {  }

glm::vec3& Player::GetPosition() { return this->_position; }

glm::vec3& Player::GetVelocity() { return this->_velocity; }

glm::vec3& Player::GetViewAngles() { return this->_viewAngles; }

Camera& Player::GetCamera() { return this->_camera; }

int Player::GetButtons() { return this->_buttons; }

void Player::SetPosition(glm::vec3& newPosition)
{
	this->_lastPosition = this->_position;
	this->_position = newPosition;
}

void Player::SetVelocity(glm::vec3& newVelocity) { this->_velocity = newVelocity; }

bool Player::IsNoclip() { return this->_isNoclip; }

bool Player::IsPressedKey(int buttons) { return this->_buttons & buttons; }

void Player::ClearVelocity() { this->_velocity = glm::vec3(0.0f); }

void Player::HandleInputs(GLFWwindow* window, float deltaTime)
{
	this->_keyInput(window);
	this->_mouseInput(window, deltaTime);
}

void Player::Update()
{
	if (this->_lastPosition != this->_position)
		this->_camera.SetPosition(this->_position);
}

// ===================================== Private =====================================

void Player::_keyInput(GLFWwindow* window)
{
	this->_lastButtons = this->_buttons;

	// 不要問我為什麼用那麼簡短的巨集
	// 因為要打一堆一樣的東西 太懶了 = =
	KEY_HANDLE(window, GLFW_KEY_W, this->_buttons, FRONT);
	KEY_HANDLE(window, GLFW_KEY_S, this->_buttons, BACK);
	KEY_HANDLE(window, GLFW_KEY_A, this->_buttons, LEFT);
	KEY_HANDLE(window, GLFW_KEY_D, this->_buttons, RIGHT);
	KEY_HANDLE(window, GLFW_KEY_LEFT_SHIFT, this->_buttons, DUCK);
	KEY_HANDLE(window, GLFW_KEY_SPACE, this->_buttons, JUMP);
	KEY_HANDLE(window, GLFW_KEY_Q, this->_buttons, YAWLEFT);
	KEY_HANDLE(window, GLFW_KEY_E, this->_buttons, YAWRIGHT);
}

void Player::_mouseInput(GLFWwindow* window, float deltaTime)
{
	// 第一次滑鼠移動事件直接忽略並置中滑鼠
	if (this->_isFirstMove)
	{
		this->_isFirstMove = false;
		glfwSetCursorPos(window, this->_windowCenterX, this->_windowCenterY);

		return;
	}

	// 獲取當前滑鼠的座標
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	// 計算滑鼠與中心點的位移量
	// 因為視窗的座標是左上角為 (0, 0)
	// 所以計算 Y 軸時要反過來
	// X 軸則因為左轉對於數學來說應為正值，所以也須反過來算
	float deltaX = this->_windowCenterX - static_cast<float>(xPos);
	float deltaY = this->_windowCenterY - static_cast<float>(yPos);

	// 如果不乘以這個 0.022f 的話移動量會很巨大
	// 所以就直接拿 CS 中的 m_yaw 跟 m_pitch 來用了 (數值都為 0.022f)
	float yaw = deltaX * 0.022f * this->_sensitivity;
	float pitch = deltaY * 0.022f * this->_sensitivity;

	// 檢查如果有使用 CS 中的 +left 或 +right 時
	bool doYawLeft = this->IsPressedKey(YAWLEFT);
	bool doYawRight = this->IsPressedKey(YAWRIGHT);

	if (doYawLeft != doYawRight)
	{
		if (doYawLeft)
			yaw += cl_yawspeed * deltaTime;
		if (doYawRight)
			yaw -= cl_yawspeed * deltaTime;
	}

	// 更新角度變化量
	this->_camera.AddEulerAngles(yaw, pitch);

	// 記得把滑鼠重新歸位至中間
	glfwSetCursorPos(window, this->_windowCenterX, this->_windowCenterY);
}
