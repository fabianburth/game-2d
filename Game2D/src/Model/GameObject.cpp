#include "GameObject.h"


GameObject::GameObject()
    : position({ 0.0f, 0.0f }), sprite() { }

GameObject::GameObject(std::array<float, 2> pos, Texture2D sprite, std::array<float, 4> size)
    : position{ pos }, sprite{ sprite }, size{ size }
{
}



//GameObject::GameObject(std::array<float,2> pos, std::array<float, 4> size, Texture2D sprite, std::array<float, 3> color, std::array<float, 2> velocity)
//    : position(pos), size(size), velocity(velocity), color(color), sprite(sprite), IsUnbreakable(true), Destroyed(false), positionToMoveTo(pos) { }

//void GameObject::destroy()
//{
//    notify();
//}

//void GameObject::yeet(Direction d, int stepRange)
//{
//    switch (d)
//    {
//    case Direction::RIGHT:
//        this->newPosition[0] = this->Position[0] + stepRange * Constants::WIDTH_UNIT;
//        break;
//    case Direction::LEFT:
//        this->newPosition[0] = this->Position[0] - stepRange * Constants::WIDTH_UNIT;
//        break;
//    case Direction::UP:
//        this->newPosition[1] = this->Position[1] + stepRange * Constants::HEIGHT_UNIT;
//        break;
//    case Direction::DOWN:
//        this->newPosition[1] = this->Position[1] - stepRange * Constants::HEIGHT_UNIT;
//        break;
//    default:
//        break;
//    }
//}

//void GameObject::Draw(SpriteRenderer& renderer)
//{
//    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Color);
//}

//void GameObject::calculateMovement(Direction d)
//{
//    switch (d)
//    {
//    case Direction::RIGHT:
//        this->newPosition[0] = this->Position[0] + Constants::WIDTH_UNIT;
//        break;
//    case Direction::LEFT:
//        this->newPosition[0] = this->Position[0] - Constants::WIDTH_UNIT;
//        break;
//    case Direction::UP:
//        this->newPosition[1] = this->Position[1] + Constants::HEIGHT_UNIT;
//        break;
//    case Direction::DOWN:
//        this->newPosition[1] = this->Position[1] - Constants::HEIGHT_UNIT;
//        break;
//    default:
//        break;
//    }
//}

//bool GameObject::move(std::array<float, 2> velocity)
//{
//    if (this->Position[0] < this->newPosition[0])
//    {
//        if (this->newPosition[0] - this->Position[0] <= velocity[0])
//        {
//            this->Position[0] = this->newPosition[0];
//            return true;
//        }
//        else
//        {
//            this->Position[0] += velocity[0];
//            return false;
//        }
//    }
//    //Movement to the left
//    if (this->Position[0] > this->newPosition[0])
//    {
//        if (this->newPosition[0] - this->Position[0] >= -velocity[0])
//        {
//            this->Position[0] = this->newPosition[0];
//            return true;
//        }
//        else
//        {
//            this->Position[0] -= velocity[0];
//            return false;
//        }
//    }
//    //Movement up
//    if (this->Position[1] < this->newPosition[1])
//    {
//        if (this->newPosition[1] - this->Position[1] <= velocity[1])
//        {
//            this->Position[1] = this->newPosition[1];
//            return true;
//        }
//        else
//        {
//            this->Position[1] += velocity[1];
//            return false;
//        }
//    }
//    //Movement down
//    if (this->Position[1] > this->newPosition[1])
//    {
//        if (this->newPosition[1] - this->Position[1] >= -velocity[1])
//        {
//            this->Position[1] = this->newPosition[1];
//            return true;
//        }
//        else
//        {
//            this->Position[1] -= velocity[1];
//            return false;
//        }
//    }
//}

void GameObject::registerObserver(Observer<GameObject>* observer)
{
    observers.push_back(observer);
}

void GameObject::removeObserver(Observer<GameObject>* observer)
{
    observers.erase(std::remove_if(observers.begin(), observers.end(),
        [&](Observer<GameObject>* comparison) {
            return comparison == observer;
        }));
}

void GameObject::notifyObservers()
{
    for (Observer<GameObject>* observer : observers)
    {
        observer->update(this);
    }
}