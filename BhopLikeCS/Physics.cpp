#include "Physics.h"

Physics::Physics(Player* player)
{
	this->_player = player;
}

Physics::~Physics() {  }

void Physics::Update(float deltaTime)
{
	this->_updateNoclip(deltaTime);

	//this->_updateGravity();
}

// ===================================== Private =====================================

void Physics::_updateNoclip(float deltaTime)
{
	if (!this->_player->IsNoclip())
		return;

	glm::vec3 front, right;
	int buttons = this->_player->GetButtons();
	this->_player->GetCamera().GetViewSpaceVectors(&front, &right, NULL);

	glm::vec3 velocity = {  };
	glm::vec3 position = this->_player->GetPosition();
	velocity += front * (float) this->_player->IsPressedKey(FRONT);
	velocity -= front * (float) this->_player->IsPressedKey(BACK);
	velocity -= right * (float) this->_player->IsPressedKey(LEFT);
	velocity += right * (float) this->_player->IsPressedKey(RIGHT);
	velocity *= sv_noclipspeed * deltaTime;
	position += velocity;

	this->_player->SetPosition(position);
}

void Physics::_updateGravity(float deltaTime)
{
	glm::vec3 velocity = this->_player->GetVelocity();
	velocity[2] -= sv_gravity * 0.5f * deltaTime;

	this->_checkVelocity(velocity);
	this->_player->SetVelocity(velocity);

	std::cout << velocity[2] << std::endl;
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
