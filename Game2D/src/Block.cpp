#include "Block.h"

Block::Block() {}

Block::Block(std::array<float, 2> pos, Texture2D sprite, bool isUnbreakable)
    :GameObject{ pos, sprite }, positionToMoveTo{ pos }, isUnbreakable{ isUnbreakable } {}

//void Block::registerObserver(const std::shared_ptr<Observer<Block*>>& observer)
//{
//    observers.push_back(observer);
//}
//
//void Block::removeObserver(const std::shared_ptr<Observer<Block*>>& observer)
//{
//    observers.erase(std::remove_if(observers.begin(), observers.end(),
//        [&](const std::shared_ptr<Observer<Block*>>& vergleich) {
//            return vergleich == observer;
//        }));
//}
//
//void Block::notifyObservers()
//{
//    for (auto& observer : observers)
//    {
//        observer->update(this);
//    }
//}

void Block::setState(BlockState state)
{
    if (this->state != state)
    {
        this->state = state;
        this->notifyObservers();
    }
}

void Block::setPositionToMoveTo(Direction d)
{
    switch (d)
    {
    case Direction::RIGHT:
        this->positionToMoveTo[0] = this->position[0] + Constants::WIDTH_UNIT;
        break;
    case Direction::LEFT:
        this->positionToMoveTo[0] = this->position[0] - Constants::WIDTH_UNIT;
        break;
    case Direction::UP:
        this->positionToMoveTo[1] = this->position[1] + Constants::HEIGHT_UNIT;
        break;
    case Direction::DOWN:
        this->positionToMoveTo[1] = this->position[1] - Constants::HEIGHT_UNIT;
        break;
    default:
        break;
    }
}

void Block::push(Direction d, int stepRange)
{
    switch (d)
    {
    case Direction::RIGHT:
        this->positionToMoveTo[0] = this->position[0] + stepRange * Constants::WIDTH_UNIT;
        break;
    case Direction::LEFT:
        this->positionToMoveTo[0] = this->position[0] - stepRange * Constants::WIDTH_UNIT;
        break;
    case Direction::UP:
        this->positionToMoveTo[1] = this->position[1] + stepRange * Constants::HEIGHT_UNIT;
        break;
    case Direction::DOWN:
        this->positionToMoveTo[1] = this->position[1] - stepRange * Constants::HEIGHT_UNIT;
        break;
    default:
        break;
    }
}

void Block::move(float deltaTime)
{
    //Movement to the right
    if (this->position[0] < this->positionToMoveTo[0])
    {
        if (this->positionToMoveTo[0] - this->position[0] <= (Block::VELOCITY[0] * deltaTime))
        {
            this->position[0] = this->positionToMoveTo[0];
            //return true;
        }
        else
        {
            this->position[0] += Block::VELOCITY[0] * deltaTime;
            //return false;
        }
    }
    //Movement to the left
    if (this->position[0] > this->positionToMoveTo[0])
    {
        if (this->positionToMoveTo[0] - this->position[0] >= -(Block::VELOCITY[0] * deltaTime))
        {
            this->position[0] = this->positionToMoveTo[0];
            //return true;
        }
        else
        {
            this->position[0] -= Block::VELOCITY[0] * deltaTime;
            //return false;
        }
    }
    //Movement up
    if (this->position[1] < this->positionToMoveTo[1])
    {
        if (this->positionToMoveTo[1] - this->position[1] <= (Block::VELOCITY[1] * deltaTime))
        {
            this->position[1] = this->positionToMoveTo[1];
            //return true;
        }
        else
        {
            this->position[1] += this->Block::VELOCITY[1] * deltaTime;
            //return false;
        }
    }
    //Movement down
    if (this->position[1] > this->positionToMoveTo[1])
    {
        if (this->positionToMoveTo[1] - this->position[1] >= -(Block::VELOCITY[1] * deltaTime))
        {
            this->position[1] = this->positionToMoveTo[1];
            //return true;
        }
        else
        {
            this->position[1] -= Block::VELOCITY[1] * deltaTime;
            //return false;
        }
    }
}
