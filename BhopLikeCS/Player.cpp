#include "Player.h"

Player::Player()
	: _camera(90.0f, g_aspectRatio)
{
	this->_position = glm::vec3(0.0f, 0.0f, 0.0f);
	this->_velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}
Player::~Player()
{

}

void Player::KeyInput(int key, int action)
{
	if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_W)
			this->_buttons |= PlayerButtons::FRONT;
		if (key == GLFW_KEY_S)
			this->_buttons |= PlayerButtons::BACK;
		if (key == GLFW_KEY_A)
			this->_buttons |= PlayerButtons::LEFT;
		if (key == GLFW_KEY_D)
			this->_buttons |= PlayerButtons::RIGHT;
		if (key == GLFW_KEY_LEFT_SHIFT)
			this->_buttons |= PlayerButtons::DUCK;
		if (key == GLFW_KEY_SPACE)
			this->_buttons |= PlayerButtons::JUMP;
	}
	else if (action == GLFW_RELEASE)
	{
		if (key == GLFW_KEY_W)
			this->_buttons &= ~PlayerButtons::FRONT;
		if (key == GLFW_KEY_S)
			this->_buttons &= ~PlayerButtons::BACK;
		if (key == GLFW_KEY_A)
			this->_buttons &= ~PlayerButtons::LEFT;
		if (key == GLFW_KEY_D)
			this->_buttons &= ~PlayerButtons::RIGHT;
		if (key == GLFW_KEY_LEFT_SHIFT)
			this->_buttons &= ~PlayerButtons::DUCK;
		if (key == GLFW_KEY_SPACE)
			this->_buttons &= ~PlayerButtons::JUMP;
	}
}

void Player::MouseInput(float dx, float dy)
{
	float yaw = dx * 0.022 * this->_sensitivity;
	float pitch = dy * 0.022 * this->_sensitivity;

	this->_camera.AddYawPitch(dx, dy);
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
//    // 傳入的數值為新的滑鼠座標與中心點的距離差
//    // 原先OpenGL與視窗的Y軸是反過來看
//    // 但變成距離差之後剛好抵銷
//    // 所以剩X軸需要反過來
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
//    // 這邊一定要做Normalize，不然會超出 [-1, 1] 的範圍
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
////    // 要處理靈敏度 (直接乘在Offset就好)
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
