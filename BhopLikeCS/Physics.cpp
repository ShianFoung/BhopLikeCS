#include "../Header.h"

#include "Physics.h"

const float sv_maxspeed = 320.0f;
const float sv_air_max_wishspeed = 30.0f;
const float sv_noclipspeed = 1000.0f;
const float sv_accelerate = 10.0f;
const float sv_airaccelerate = 1000.0f;
const float sv_maxvelocity = 3500.0f;
const float sv_gravity = 800.0f;
const float sv_friction = 4.8f;
const float cl_forwardspeed = 450.0f;
const float cl_sidespeed = 450.0f;
const float cl_upspeed = 320.0f;
const float sv_stopspeed = 80.0f;

Physics::Physics(Player& player, std::vector<BoundingBox>& boundingBoxes)
{
    this->player = &player;
    this->boundingBoxes = &boundingBoxes;
}

void Physics::Update(float frameTime)
{
    this->frameTime = frameTime;
    this->previousButtons = this->player->GetPreviousButtons();
    this->buttons = this->player->GetButtons();

    if (this->player->GetStates() & PlayerStates::NOCLIPMODE)
        this->updateNoclip();
    else
        this->updateMove();
}

void Physics::updateNoclip()
{
    glm::vec3 front = this->player->GetCamera().GetFrontVector();
    glm::vec3 right = this->player->GetCamera().GetRightVector();
    int buttons = this->player->GetButtons();
    glm::vec3 velocity {  };
    glm::vec3 position = this->player->GetPosition();
    
    velocity += front * (float) this->player->IsKeyPressed(FRONT);
    velocity -= front * (float) this->player->IsKeyPressed(BACK);
    velocity -= right * (float) this->player->IsKeyPressed(LEFT);
    velocity += right * (float) this->player->IsKeyPressed(RIGHT);
    velocity *= sv_noclipspeed;

    this->player->SetVelocity(velocity);
    this->player->SetPosition(this->player->GetPosition() + velocity * this->frameTime);
}

void Physics::updateMove()
{
    this->getMoveData();

    // TODO: 之後再作
    // this->checkDuck();

    this->gravity();

    // 玩家跳躍
    // 為什麼這裡是這個奇怪的數字而不是 sv_gravity 800
    // 看原始碼中有一個叫 g_bMovementOptimizations 的數值，預設都是開啟
    // 不然的話數值會是 sqrt(2.0f * sv_gravity.GetFloat() * 21.0f)
    if (this->player->IsKeyPressed(PlayerButtons::JUMP) && this->player->GetStates() & PlayerStates::ONGROUND)
    {
        this->player->GetVelocity().z += 268.3281572999747f;
        this->player->RemoveStates(PlayerStates::ONGROUND);
    }

    if (this->player->GetStates() & PlayerStates::ONGROUND)
    {
        this->friction();
        this->walkMove();
    }
    else
        this->airMove();

    // 檢測玩家的碰撞
    this->checkCollision();
}

void Physics::checkDuck()
{
    // 上一次沒有蹲下但這一次有
    if (!(this->previousButtons & PlayerButtons::DUCK) && (this->buttons & PlayerButtons::DUCK))
    {
        // 如果玩家在地上，將視野跟玩家高度往下調
        // 如果在空中，則視野不會動，但玩家的下方高度會往上縮
        if (this->player->GetStates() & PlayerStates::ONGROUND)
        {

        }
        else
        {

        }
    }

    // 上一次是蹲下但這一次放開
    if ((this->previousButtons & PlayerButtons::DUCK) && !(this->buttons & PlayerButtons::DUCK))
    {
        // 如果玩家在地上，將視野跟玩家高度往上調
        // 如果在空中，則視野不動，但玩家的下方高度會往下伸
        if (this->player->GetStates() & PlayerStates::ONGROUND)
        {

        }
        else
        {

        }
    }
}

void Physics::checkCollision()
{
    float inverseFrameTime = 1.0f / this->frameTime;
    glm::vec3 newVelocity = this->player->GetVelocity() * this->frameTime;
    glm::vec3 currentPosition = this->player->GetPosition();
    BoundingBox currentPosBBox = BoundingBox::FromPlayer(currentPosition, 16.0f, 72.0f);

    // 我們是三維空間，所以要做 3 次碰撞測試
    for (int i = 0; i < 3; i++)
    {
        BoundingBox newPosBBox = BoundingBox::FromPlayer(currentPosition + newVelocity, 16.0f, 72.0f);
        BoundingBox collisionArea = BoundingBox::FromTwoBoundingBoxes(currentPosBBox, newPosBBox);

        glm::vec3 hitNormal(0.0f);
        float minMovingTime = 1.0f;
        glm::vec3 minHitNormal(0.0f);

        for (BoundingBox& box : *this->boundingBoxes)
        {
            if (collisionArea.IntersectWithBox(box))
            {
                float movingTime = utils::SweptAABB(currentPosBBox, newVelocity, box, hitNormal);

                if (movingTime < minMovingTime)
                {
                    minMovingTime = movingTime;
                    minHitNormal = hitNormal;
                }
            }
        }

        if (minMovingTime == 1.0f)
            continue;

        currentPosition += newVelocity * minMovingTime;
        float remainingTime = 1.0f - minMovingTime;
        newVelocity *= remainingTime;

        if (minHitNormal.x != 0.0f)
        {
            newVelocity.x = 0.0f;
            this->player->GetVelocity().x = 0.0f;
        }
        else if (minHitNormal.y != 0.0f)
        {
            newVelocity.y = 0.0f;
            this->player->GetVelocity().y = 0.0f;
        }
        else
        {
            newVelocity.z = 0.0f;
            this->player->GetVelocity().z = 0.0f;

            if (minHitNormal.z == 1.0f)
            {
                if (this->player->IsKeyPressed(PlayerButtons::JUMP))
                {
                    newVelocity.z += 268.3281572999747f * this->frameTime;
                    this->player->GetVelocity().z += 268.3281572999747f;
                }
                else
                    this->player->AddStates(PlayerStates::ONGROUND);
            }
        }
    }

    this->player->SetPosition(currentPosition + newVelocity);
}

void Physics::getMoveData()
{
    this->frontMove = 0.0f;
    this->rightMove = 0.0f;
    this->upMove = 0.0f;

    this->frontMove += cl_forwardspeed * this->player->IsKeyPressed(PlayerButtons::FRONT);
    this->frontMove -= cl_forwardspeed * this->player->IsKeyPressed(PlayerButtons::BACK);
    this->rightMove -= cl_sidespeed * this->player->IsKeyPressed(PlayerButtons::LEFT);
    this->rightMove += cl_sidespeed * this->player->IsKeyPressed(PlayerButtons::RIGHT);
    this->upMove += cl_upspeed * this->player->IsKeyPressed(PlayerButtons::JUMP);

    float speed = this->frontMove * this->frontMove +
                  this->rightMove * this->rightMove +
                  this->upMove * this->upMove;

    if (speed != 0.0f && speed > sv_maxspeed * sv_maxspeed)
    {
        float ratio = sv_maxspeed / std::sqrtf(speed);
        this->frontMove *= ratio;
        this->rightMove *= ratio;
        this->upMove *= ratio;
    }
}

void Physics::gravity()
{
    this->player->GetVelocity().z -= sv_gravity * this->frameTime;

    this->checkVelocity();
}

void Physics::checkVelocity()
{
    glm::vec3* velocity = &this->player->GetVelocity();

    for (int i = 0; i < 3; i++)
    {
        if ((*velocity)[i] > sv_maxvelocity)
            (*velocity)[i] = sv_maxvelocity;

        if ((*velocity)[i] < -sv_maxvelocity)
            (*velocity)[i] = -sv_maxvelocity;
    }
}

void Physics::friction()
{
    float speed = glm::length(this->player->GetVelocity());

    if (speed < 0.1f)
        return;

    float control = speed < sv_stopspeed ? sv_stopspeed : speed;
    float drop = control * sv_friction * this->frameTime;
    float newSpeed = speed - drop;

    if (newSpeed < 0.0f)
        newSpeed = 0.0f;

    if (newSpeed != speed)
    {
        newSpeed /= speed;
        this->player->GetVelocity() *= newSpeed;
    }
}

void Physics::walkMove()
{
    glm::vec3 front = this->player->GetCamera().GetFrontVector();
    glm::vec3 right = this->player->GetCamera().GetRightVector();

    if (front.z != 0.0f)
    {
        front.z = 0.0f;
        front = glm::normalize(front);
    }

    if (right.z != 0.0f)
    {
        right.z = 0.0f;
        right = glm::normalize(right);
    }

    glm::vec3 wishVelocity = front * this->frontMove + right * this->rightMove;
    wishVelocity.z = 0.0f;

    glm::vec3 wishDirection = wishVelocity;
    float wishSpeed = utils::GetVectorLengthAndNormalize(wishDirection);

    if ((wishSpeed != 0.0f) && (wishSpeed > sv_maxspeed))
    {
        wishVelocity *= sv_maxspeed / wishSpeed;
        wishSpeed = sv_maxspeed;
    }

    this->player->GetVelocity().z = 0.0f;
    this->accelerate(wishDirection, wishSpeed);

    if (utils::GetVectorLengthSqr(this->player->GetVelocity()) > sv_maxspeed * sv_maxspeed)
    {
        float ratio = sv_maxspeed / glm::length(this->player->GetVelocity());
        this->player->GetVelocity() *= ratio;
    }
}

void Physics::airMove()
{
    glm::vec3 front = this->player->GetCamera().GetFrontVector();
    glm::vec3 right = this->player->GetCamera().GetRightVector();
    front.z = 0.0f;
    right.z = 0.0f;
    front = glm::normalize(front);
    right = glm::normalize(right);

    glm::vec3 wishVelocity = front * this->frontMove + right * this->rightMove;
    wishVelocity.z = 0.0f;

    glm::vec3 wishDirection = wishVelocity;
    float wishSpeed = utils::GetVectorLengthAndNormalize(wishDirection);

    if ((wishSpeed != 0.0f) && (wishSpeed > sv_maxspeed))
    {
        wishVelocity *= sv_maxspeed / wishSpeed;
        wishSpeed = sv_maxspeed;
    }

    this->airAccelerate(wishDirection, wishSpeed);
}

void Physics::accelerate(const glm::vec3& wishDirection, const float wishSpeed)
{
    float currentSpeed = glm::dot(this->player->GetVelocity(), wishDirection);
    float addSpeed = wishSpeed - currentSpeed;

    if (addSpeed <= 0.0f)
        return;

    float accelerationScale = std::max(250.0f, wishSpeed);
    float accelerateSpeed = sv_accelerate * this->frameTime * accelerationScale;

    if (accelerateSpeed > addSpeed)
        accelerateSpeed = addSpeed;

    this->player->GetVelocity() += accelerateSpeed * wishDirection;
}

void Physics::airAccelerate(const glm::vec3& wishDirection, float wishSpeed)
{
    if (wishSpeed > 30.0f)
        wishSpeed = 30.0f;

    float currentSpeed = glm::dot(this->player->GetVelocity(), wishDirection);
    float addSpeed = wishSpeed - currentSpeed;

    if (addSpeed <= 0.0f)
        return;

    float accelerateSpeed = sv_airaccelerate * wishSpeed * this->frameTime;

    if (accelerateSpeed > addSpeed)
        accelerateSpeed = addSpeed;

    this->player->GetVelocity() += accelerateSpeed * wishDirection;
}
