#include "Physics.h"

Physics::Physics(Player* player)
{
	this->_player = player;
}

Physics::~Physics() {  }

void Physics::Update(float deltaTime)
{
	
}

// ===================================== Private =====================================

void Physics::_gravity(float deltaTime)
{
	glm::vec3 velocity = this->_player->GetVelocity();

	velocity[2] -= sv_gravity * 0.5f * deltaTime;

	this->_checkVelocity(velocity);

	this->_player->SetVelocity(velocity);
}

void Physics::_checkVelocity(glm::vec3& velocity)
{
	for (int i = 0; i < 3; i++)
	{
		if (velocity[i] > sv_maxvelocity)
			velocity[i] = sv_maxvelocity;
		else if (velocity[i] < -sv_maxvelocity)
			velocity[i] = -sv_maxvelocity;
	}
}
