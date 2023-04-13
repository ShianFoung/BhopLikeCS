#pragma once

#include "GameHeader.h"

#include "Camera.h"

#include <glm/glm.hpp>

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
	Player();
	~Player();

	glm::mat4 GetViewProjectionMatrix() { return this->_camera.GetViewProjectionMatrix(); }

	void KeyInput(int key, int action);
	void MouseInput(float dx, float dy);
	void CreateMove();
	void Update();

	void Temp(GLFWwindow* window)
	{
		this->_camera.Temp(window);
	}
private:
	Camera _camera;
	glm::vec3 _position;
	glm::vec3 _velocity;

	float _sensitivity = 1.0f;
	int _buttons = 0;
};

//
//#include "Camera.h"
//
//#include "GLHeader.h"
//
//#include <glm/glm.hpp>
//
//enum PlayerButtons : int
//{
//    FRONT = (1 << 0),
//    BACK = (1 << 1),
//    LEFT = (1 << 2),
//    RIGHT = (1 << 3),
//    JUMP = (1 << 4),
//    DUCK = (1 << 5),
//    YAWLEFT = (1 << 6),
//    YAWRIGHT = (1 << 7)
//};
//
//class Player
//{
//public:
//    Player(float aspectRatio, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f));
//    ~Player();
//
//    const glm::mat4& GetProjectionViewMatrix() { return this->_camera.GetProjectionViewMatrix(); }
//
//    const glm::vec3& GetPosition() { return this->_position; }
//    const glm::vec3& GetAbsPosition() { return glm::abs(this->_position); }
//    const glm::vec3& GetVelocity() { return this->_velocity; }
//
//    void UpdateKeyInput(GLFWwindow* window);
//    void UpdateMouseInput(double dx, double dy);
//private:
//    Camera _camera;
//
//    glm::vec3 _position;
//    glm::vec3 _velocity;
//
//    /*double _lastMouseXPos = 0.0f;
//    double _lastMouseYPos = 0.0f;*/
//};
////
////class Player
////{
////public:
////    Player(int windowWidth, int windowHeight);
////    ~Player();
////
////    Camera* GetCamera() { return &this->_camera; }
////
////    void UpdateKeyInput(int key, int action);
////    void UpdateMouseInput(double xPos, double yPos);
////    void Update();
////private:
////    const glm::vec3 _normalBBox = glm::vec3(32.0f, 72.0f, 32.0f);
////    const glm::vec3 _crouchBBox = glm::vec3(32.0f, 54.0f, 32.0f);
////    const float normalEyeLevel = 64.0f;
////    const float crouchEyeLevel = 46.0f;
////
////    Camera _camera;
////
////    int _buttons = 0;
////    double _lastMouseXPos = 0.0;
////    double _lastMouseYPos = 0.0;
////
////    void _pressButton(int button);
////    void _releaseButton(int button);
////};
