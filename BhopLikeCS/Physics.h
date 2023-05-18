#pragma once

#include "Header.h"

#include "Player.h"

static float sv_noclipspeed = 1000.0f;
static float sv_accelerate = 5.5f;
static float sv_airaccelerate = 1000.0f;
static float sv_maxvelocity = 3500.0f;
static float sv_gravity = 800.0f;
static float sv_friction = 4.0f;
static float cl_upspeed = 320.0f;
static float cl_movespeed = 400.0f;

class Physics
{
public:
	Physics(Player* player);
	~Physics();

	void Update(float deltaTime);
private:
	Player* _player;

	void _updateNoclip(float deltaTime);
	void _updateGravity(float deltaTime);
	void _checkVelocity(glm::vec3& velocity);
};
