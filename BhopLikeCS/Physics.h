#pragma once

#include "Player.h"
#include "../Data/BoundingBox.h"

class Physics
{
public:
    Physics(Player& player, std::vector<BoundingBox>& boundingBoxes);

    void Update(float frameTime);
private:
    Player* player;
    std::vector<BoundingBox>* boundingBoxes;

    float frameTime;
    int previousButtons;
    int buttons;

    float frontMove;
    float rightMove;
    float upMove;

    void updateNoclip();
    void updateMove();

    void checkVelocity();
    void checkDuck();
    void checkCollision();

    void getMoveData();
    void gravity();
    void friction();
    void walkMove();
    void airMove();
    void accelerate(const glm::vec3& wishDirection, const float wishSpeed);
    void airAccelerate(const glm::vec3& wishDirection, float wishSpeed);

};

//class Physics
//{
//public:
//	Physics(Player* player);
//	~Physics();
//
//	void Update(float deltaTime);
//private:
//	Player* _player;
//
//	void _updateNoclip(float deltaTime);
//	void _updateGravity(float deltaTime);
//	void _checkVelocity(glm::vec3& velocity);
//};
