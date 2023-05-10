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

Camera& Player::GetCamera() { return this->_camera; }

void Player::HandleInputs(GLFWwindow* window)
{
	this->_keyInput(window);
	this->_mouseInput(window);
}

// ===================================== Private =====================================

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
	float deltaX = static_cast<float>(xPos) - this->_windowCenterX;
	float deltaY = this->_windowCenterY - static_cast<float>(yPos);

	// �p�G�����H�o�� 0.022f ���ܲ��ʶq�|�ܥ��j
	// �ҥH�N������ CS ���� m_yaw �� m_pitch �ӥΤF (�ƭȳ��� 0.022f)
	float yaw = deltaX * 0.022f * this->_sensitivity;
	float pitch = deltaY * 0.022f * this->_sensitivity;

	this->_camera.AddCameraAngles(yaw, pitch);

	// �O�o��ƹ����s�k��ܤ���
	glfwSetCursorPos(window, this->_windowCenterX, this->_windowCenterY);
}

//
//Player::Player(float aspectRatio, glm::vec3 position, glm::vec3 direction)
//    : _camera(60.0f, aspectRatio, 0.1f, 1000.0f)
//{
//    this->_position = position;
//    this->_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
//}
//
//Player::~Player() {  }
//
//void Player::UpdateKeyInput(GLFWwindow* window)
//{
//    this->_camera.KeyInput(window);
//}
//
//void Player::UpdateMouseInput(double dx, double dy)
//{
//    // �ǤJ���ƭȬ��s���ƹ��y�лP�����I���Z���t
//    // ���OpenGL�P������Y�b�O�ϹL�Ӭ�
//    // ���ܦ��Z���t�����n��P
//    // �ҥH��X�b�ݭn�ϹL��
//    dx = -dx;
//
//    float yaw = this->_camera.GetYaw();
//    float pitch = this->_camera.GetPitch();
//
//    yaw += dx * 0.1;
//    pitch += dy * 0.1;
//
//    if (yaw > 180.0f)
//        yaw -= 360.0f;
//
//    if (yaw < -180.0f)
//        yaw += 360.0f;
//
//    if (pitch > 89.0f)
//        pitch = 89.0f;
//
//    if (pitch < -89.0f)
//        pitch = -89.0f;
//
//
//    float yawRadians = glm::radians(yaw);
//    float pitchRadians = glm::radians(pitch);
//    glm::vec3 direction {};
//
//    direction.x = cos(pitchRadians) * cos(yawRadians);
//    direction.y = sin(pitchRadians);
//    direction.z = cos(pitchRadians) * sin(yawRadians);
//    // �o��@�w�n��Normalize�A���M�|�W�X [-1, 1] ���d��
//    direction = glm::normalize(direction);
//
//    this->_camera.SetCameraDirection(direction);
//    this->_camera.SetYawPitch(yaw, pitch);
//}
//
////void Player::UpdateKeyInput(int key, int action)
////{
////    int button = 0;
////
////    if (action == GLFW_PRESS)
////    {
////        switch (key)
////        {
////            case GLFW_KEY_W:
////                button = PlayerButtons::FRONT;
////                break;
////            case GLFW_KEY_S:
////                button = PlayerButtons::BACK;
////                break;
////            case GLFW_KEY_A:
////                button = PlayerButtons::LEFT;
////                break;
////            case GLFW_KEY_D:
////                button = PlayerButtons::RIGHT;
////                break;
////            case GLFW_KEY_SPACE:
////                button = PlayerButtons::JUMP;
////                break;
////            case GLFW_KEY_LEFT_CONTROL:
////                button = PlayerButtons::DUCK;
////                break;
////            default:
////                break;
////        }
////
////        this->_pressButton(button);
////    }
////    else if (action == GLFW_RELEASE)
////    {
////        switch (key)
////        {
////            case GLFW_KEY_W:
////                button = PlayerButtons::FRONT;
////                break;
////            case GLFW_KEY_S:
////                button = PlayerButtons::BACK;
////                break;
////            case GLFW_KEY_A:
////                button = PlayerButtons::LEFT;
////                break;
////            case GLFW_KEY_D:
////                button = PlayerButtons::RIGHT;
////                break;
////            case GLFW_KEY_SPACE:
////                button = PlayerButtons::JUMP;
////                break;
////            case GLFW_KEY_LEFT_CONTROL:
////                button = PlayerButtons::DUCK;
////                break;
////            default:
////                break;
////        }
////
////        this->_releaseButton(button);
////    }
////}
////
////void Player::UpdateMouseInput(double xPos, double yPos)
////{
////    float xOffset = xPos - this->_lastMouseXPos;
////    float yOffset = this->_lastMouseYPos - yPos;
////
////    this->_lastMouseXPos = xPos;
////    this->_lastMouseYPos = yPos;
////
////    // �n�B�z�F�ӫ� (�������bOffset�N�n)
////
////    float yaw = this->_camera.GetYaw();
////    float pitch = this->_camera.GetPitch();
////
////    yaw += xOffset;
////    pitch += yOffset;
////
////    if (yaw > 180.0f)
////        yaw -= 360.0f;
////    
////    if (yaw < -180.0f)
////        yaw += 360.0f;
////
////    if (pitch > 89.0f)
////        pitch -= 89.0f;
////
////    if (pitch < -89.0f)
////        pitch += 89.0f;
////
////    float yawRadians = glm::radians(yaw);
////    float pitchRadians = glm::radians(pitch);
////
////    glm::vec3 direction;
////
////    direction.x = cos(yawRadians) * sin(pitchRadians);
////    direction.y = sin(pitchRadians);
////    direction.z = sin(yawRadians) * cos(pitchRadians);
////    direction = glm::normalize(direction);
////
////    this->_camera.SetCameraDirection(direction);
////}
////
////void Player::Update()
////{
////    if (this->_buttons > 0)
////    {
////        std::bitset<8> b(this->_buttons);
////        std::cout << b << std::endl;
////    }
////
////    glm::vec3 pos = this->_camera.GetCameraPosition();
////    glm::vec3 direction = this->_camera.GetCameraDirection();
////    glm::vec3 up = this->_camera.GetCameraUp();
////
////    if (this->_buttons & PlayerButtons::FRONT)
////        pos += 0.0005f * direction;
////
////    if (this->_buttons & PlayerButtons::BACK)
////        pos -= 0.0005f * direction;
////
////    if (this->_buttons & PlayerButtons::LEFT)
////        pos -= 0.0005f * glm::normalize(glm::cross(direction, up));
////
////    if (this->_buttons & PlayerButtons::RIGHT)
////        pos += 0.0005f * glm::normalize(glm::cross(direction, up));
////
////    if (this->_buttons > 0)
////    {
////        std::cout << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
////    }
////
////    this->_camera.SetCameraPosition(pos);
////}
////
////// ===================================== Private =====================================
////
////void Player::_pressButton(int button)
////{
////    this->_buttons |= button;
////}
////
////void Player::_releaseButton(int button)
////{
////    this->_buttons &= ~button;
////}
