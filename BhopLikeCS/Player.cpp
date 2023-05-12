#include "Player.h"

Player::Player(float fov, float windowWidth, float windowHeight)
	: _camera(fov, windowWidth / windowHeight)
{
	this->_position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->_windowWidth = windowWidth;
	this->_windowHeight = windowHeight;
	this->_windowCenterX = this->_windowWidth / 2.0f;
	this->_windowCenterY = this->_windowHeight / 2.0f;

	glm::vec3 cameraOffset = glm::vec3(0.0f, 0.0f, 64.0f);

	this->_camera.SetCameraPositionOffset(cameraOffset);
}
Player::~Player() {  }

glm::vec3& Player::GetVelocity() { return this->_velocity; }

Camera& Player::GetCamera() { return this->_camera; }

void Player::SetVelocity(glm::vec3& newVelocity) { this->_velocity = newVelocity; }

bool Player::IsNoclip() { return this->_isNoclip; }

void Player::HandleInputs(GLFWwindow* window)
{
	this->_mouseInput(window);
	this->_keyInput(window);
}

void Player::Update(float deltaTime)
{

}

// ===================================== Private =====================================

void Player::_mouseInput(GLFWwindow* window)
{
	// �Ĥ@���ƹ����ʨƥ󪽱������øm���ƹ�
	if (this->_isFirstMove)
	{
		this->_isFirstMove = false;

		glfwSetCursorPos(window, this->_windowCenterX, this->_windowCenterY);

		return;
	}

	// �����e�ƹ����y��
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	// �p��ƹ��P�����I���첾�q
	// �]���������y�ЬO���W���� (0, 0)
	// �ҥH�p�� Y �b�ɭn�ϹL��
	// X �b�h�]��������ƾǨӻ��������ȡA�ҥH�]���ϹL�Ӻ�
	float deltaX = this->_windowCenterX - static_cast<float>(xPos);
	float deltaY = this->_windowCenterY - static_cast<float>(yPos);

	// �p�G�����H�o�� 0.022f ���ܲ��ʶq�|�ܥ��j
	// �ҥH�N������ CS ���� m_yaw �� m_pitch �ӥΤF (�ƭȳ��� 0.022f)
	float yaw = deltaX * 0.022f * this->_sensitivity;
	float pitch = deltaY * 0.022f * this->_sensitivity;

	// ��s�����ܤƶq
	this->_camera.AddCameraAngles(yaw, pitch);

	// �O�o��ƹ����s�k��ܤ���
	glfwSetCursorPos(window, this->_windowCenterX, this->_windowCenterY);
}

void Player::_keyInput(GLFWwindow* window)
{
	this->_lastButtons = this->_buttons;

	// ���n�ݧڬ�����Ψ���²�u������
	// �]���n���@��@�˪��F�� ���i�F = =
	KEY_HANDLE(window, GLFW_KEY_W, this->_buttons, PlayerButtons::FRONT);
	KEY_HANDLE(window, GLFW_KEY_S, this->_buttons, PlayerButtons::BACK);
	KEY_HANDLE(window, GLFW_KEY_A, this->_buttons, PlayerButtons::LEFT);
	KEY_HANDLE(window, GLFW_KEY_D, this->_buttons, PlayerButtons::RIGHT);
	KEY_HANDLE(window, GLFW_KEY_LEFT_SHIFT, this->_buttons, PlayerButtons::DUCK);
	KEY_HANDLE(window, GLFW_KEY_SPACE, this->_buttons, PlayerButtons::JUMP);
}
