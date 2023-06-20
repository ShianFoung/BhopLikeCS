#include "../Header.h"

#include "Player.h"

Player::Player(const float fov, const int windowWidth, const int windowHeight)
    : windowHalfWidth(windowWidth * 0.5f), windowHalfHeight(windowHeight * 0.5f),
    camera(fov, static_cast<float>(windowWidth) / static_cast<float>(windowHeight))
{
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    this->sensitivity = 1.6f;
    this->previousButtons = 0;
    this->buttons = 0;
    this->states = PlayerStates::ONGROUND;
}

Camera& Player::GetCamera()
{
    return this->camera;
}

glm::vec3& Player::GetPosition()
{
    return this->position;
}

glm::vec3& Player::GetVelocity()
{
    return this->velocity;
}

int Player::GetPreviousButtons()
{
    return this->previousButtons;
}

int Player::GetButtons()
{
    return this->buttons;
}

int Player::GetStates()
{
    return this->states;
}

void Player::SetSensitivity(const float sensitivity)
{
    this->sensitivity = sensitivity;
}

void Player::SetPosition(const glm::vec3& position)
{
    this->position = position;
}

void Player::SetVelocity(const glm::vec3& velocity)
{
    this->velocity = velocity;
}

void Player::AddStates(int states)
{
    this->states |= states;
}

void Player::RemoveStates(int states)
{
    this->states &= ~states;
}

bool Player::IsKeyPressed(int button)
{
    return this->buttons & button;
}

void Player::HandleInputs(GLFWwindow* window, float frameTime)
{
    this->keyInput(window);
    this->mouseInput(window, frameTime);
}

void Player::Update(float frameTime)
{
    /*if (this->states & PlayerStates::ONGROUND)
        this->velocity.z = 0.0f;*/

    //this->position += this->velocity * frameTime;

    /*if (this->position.z < 0.0f)
    {
        this->states |= PlayerStates::ONGROUND;
        this->position.z = 0.0f;
    }*/

    glm::vec3 cameraPosition = this->position;
    cameraPosition.z += Player::StandingEyeLevel;

    this->camera.SetPosition(cameraPosition);
    this->camera.Update();
}

inline void Player::keyInput(GLFWwindow* window)
{
    this->previousButtons = buttons;

    // 處理玩家輸入
    this->setButton(window, GLFW_KEY_W, PlayerButtons::FRONT);
    this->setButton(window, GLFW_KEY_S, PlayerButtons::BACK);
    this->setButton(window, GLFW_KEY_A, PlayerButtons::LEFT);
    this->setButton(window, GLFW_KEY_D, PlayerButtons::RIGHT);
    this->setButton(window, GLFW_KEY_LEFT_SHIFT, PlayerButtons::DUCK);
    this->setButton(window, GLFW_KEY_SPACE, PlayerButtons::JUMP);
    this->setButton(window, GLFW_KEY_V, PlayerButtons::YAWLEFT);
    this->setButton(window, GLFW_KEY_B, PlayerButtons::YAWRIGHT);

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        this->states |= PlayerStates::NOCLIPMODE;
        this->states &= ~PlayerStates::ONGROUND;
    }

    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        this->states &= ~PlayerStates::NOCLIPMODE;

    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
    {
        this->position = glm::vec3(0.0f, 0.0f, 72.0f);
        this->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    }
}

inline void Player::mouseInput(GLFWwindow* window, float frameTime)
{
    if (this->isFirstMove)
    {
        this->isFirstMove = false;
        glfwSetCursorPos(window, this->windowHalfWidth, this->windowHalfHeight);
        return;
    }

    // 獲取當前滑鼠的座標
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	// 計算滑鼠與中心點的位移量
	// 因為視窗的座標是左上角為 (0, 0)
	// 所以計算 Y 軸時要反過來
	// X 軸則因為左轉對於數學來說應為正值，所以也須反過來算
	float deltaX = this->windowHalfWidth - static_cast<float>(xPos);
	float deltaY = this->windowHalfHeight - static_cast<float>(yPos);

	// 如果不乘以這個 0.022f 的話移動量會很巨大
	// 所以就直接拿 CS 中的 m_yaw 跟 m_pitch 來用了 (數值都為 0.022f)
	float yaw = deltaX * 0.022f * this->sensitivity;
	float pitch = deltaY * 0.022f * this->sensitivity;

    // TODO: 210.0f 要替換成 cl_yawspeed
    // 處理 +left 與 +right 的部分
    yaw += 210.0f * frameTime * this->IsKeyPressed(PlayerButtons::YAWLEFT);
    yaw -= 210.0f * frameTime * this->IsKeyPressed(PlayerButtons::YAWRIGHT);

	// 更新角度變化量
    this->camera.AddViewAngles(yaw, pitch);

    glfwSetCursorPos(window, this->windowHalfWidth, this->windowHalfHeight);
}

inline void Player::setButton(GLFWwindow* window, int key, PlayerButtons button)
{
    if (glfwGetKey(window, key) == GLFW_PRESS)
        this->buttons |= button;
    else
        this->buttons &= ~button;
}
