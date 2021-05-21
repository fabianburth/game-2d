#include "Player.h"
#include "ResourceManager.h"
#include "Animator.h"

Player::Player() {}

Player::Player(std::array<float, 2> pos, Texture2D sprite, std::array<float, 2> velocity)
    :GameObject{ pos, sprite }, velocity{ velocity }, positionToMoveTo{ pos }, ready{ true }, toggleSprite{ true } {}

void Player::setDirection(Direction direction)
{
    if (this->direction != direction)
    {
        this->direction = direction;
        this->notifyObservers();
    }
}

void Player::setState(PengoState state)
{
    if (this->state != state)
    {
        this->state = state;
        this->notifyObservers();
    }
}

void Player::move(float deltaTime)
{
	if (this->position[0] < this->positionToMoveTo[0])
        {
            if (this->positionToMoveTo[0] - this->position[0] <= (this->velocity[0] * deltaTime)) 
            {
                this->position[0] = this->positionToMoveTo[0];
                setState(PengoState::STAND);
                this->ready = true;
            }
            else
                this->position[0] += this->velocity[0] * deltaTime;
        }
        //Movement to the left
        if (this->position[0] > this->positionToMoveTo[0])
        {
            if (this->positionToMoveTo[0] - this->position[0] >= -(this->velocity[0] * deltaTime))
            {
                this->position[0] = this->positionToMoveTo[0];
                setState(PengoState::STAND);
                this->ready = true;
            }
            else
                this->position[0] -= this->velocity[0] * deltaTime;
        }
        //Movement up
        if (this->position[1] < this->positionToMoveTo[1])
        {
            if (this->positionToMoveTo[1] - this->position[1] <= (this->velocity[1] * deltaTime))
            {
                this->position[1] = this->positionToMoveTo[1];
                setState(PengoState::STAND);
                this->ready = true;
            }
            else
                this->position[1] += this->velocity[1] * deltaTime;
        }
        //Movement down
        if (this->position[1] > this->positionToMoveTo[1])
        {
            if (this->positionToMoveTo[1] - this->position[1] >= -(this->velocity[1] * deltaTime))
            {
                this->position[1] = this->positionToMoveTo[1];
                setState(PengoState::STAND);
                this->ready = true;
            }
            else
                this->position[1] -= this->velocity[1] * deltaTime;
        }
}

void Player::swapSprite()
{
    if (toggleSprite)
    {
        toggleSprite = false;
        this->sprite = ResourceManager::GetTexture("pengo" + stringDirection(this->direction));
    }
    else
    {
        toggleSprite = true;
        this->sprite = ResourceManager::GetTexture("pengoMove" + stringDirection(this->direction));
    }
}

void Player::setPositionToMoveTo()
{
    switch (this->direction)
    {
    case Direction::RIGHT:
        this->positionToMoveTo[0] = this->position[0] + Constants::WIDTH_UNIT;
        this->ready = false;
        break;
    case Direction::LEFT:
        this->positionToMoveTo[0] = this->position[0] - Constants::WIDTH_UNIT;
        this->ready = false;
        break;
    case Direction::UP:
        this->positionToMoveTo[1] = this->position[1] + Constants::HEIGHT_UNIT;
        this->ready = false;
        break;
    case Direction::DOWN:
        this->positionToMoveTo[1] = this->position[1] - Constants::HEIGHT_UNIT;
        this->ready = false;
        break;
    default:
        break;
    }
}

//void Player::registerObserver(const std::shared_ptr<Observer<Player*>>& observer)
//{
//    observers.push_back(observer);
//}
//
//void Player::removeObserver(const std::shared_ptr<Observer<Player*>>& observer)
//{
//    observers.erase(std::remove_if(observers.begin(), observers.end(),
//        [&](const std::shared_ptr<Observer<Player*>>& vergleich) {
//            return vergleich == observer;
//        }));
//}
//
//void Player::notifyObservers()
//{
//    for (auto& observer : observers)
//    {
//        observer->update(this);
//    }
//}
