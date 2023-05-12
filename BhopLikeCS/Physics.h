#pragma once

#include "GameHeader.h"

#include "Player.h"

static float sv_accelerate = 5.5f;
static float sv_airaccelerate = 1000.0f;
static float sv_maxvelocity = 3500.0f;
static float sv_gravity = 800.0f;

class Physics
{
public:
	Physics(Player* player);
	~Physics();

	void Update(float deltaTime);
private:
	Player* _player;

	void _gravity(float deltaTime);
	void _checkVelocity(glm::vec3& velocity);
};
