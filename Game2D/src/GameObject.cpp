#include "gameobject.h"


GameObject::GameObject()
    : Position({ 0.0f, 0.0f }), Size({ 1.0f, 1.0f }), Velocity({ 0.0f, 0.0f }), Color({ 1.0f, 1.0f, 1.0f }), Sprite(), IsSolid(false), Destroyed(false) { }

GameObject::GameObject(std::array<float,2> pos, std::array<float, 4> size, Texture2D sprite, std::array<float, 3> color, std::array<float, 2> velocity)
    : Position(pos), Size(size), Velocity(velocity), Color(color), Sprite(sprite), IsSolid(true), Destroyed(false), newPosition(pos) { }

void GameObject::destroy()
{
    notify();
}

void GameObject::yeet(Direction d, int stepRange)
{
    switch (d)
    {
    case Direction::RIGHT:
        this->newPosition[0] = this->Position[0] + stepRange * WIDTH_UNIT;
        break;
    case Direction::LEFT:
        this->newPosition[0] = this->Position[0] - stepRange * WIDTH_UNIT;
        break;
    case Direction::UP:
        this->newPosition[1] = this->Position[1] + stepRange * HEIGHT_UNIT;
        break;
    case Direction::DOWN:
        this->newPosition[1] = this->Position[1] - stepRange * HEIGHT_UNIT;
        break;
    default:
        break;
    }
}

void GameObject::Draw(SpriteRenderer& renderer)
{
    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Color);
}

void GameObject::calculateMovement(Direction d)
{
    switch (d)
    {
    case Direction::RIGHT:
        this->newPosition[0] = this->Position[0] + WIDTH_UNIT;
        break;
    case Direction::LEFT:
        this->newPosition[0] = this->Position[0] - WIDTH_UNIT;
        break;
    case Direction::UP:
        this->newPosition[1] = this->Position[1] + HEIGHT_UNIT;
        break;
    case Direction::DOWN:
        this->newPosition[1] = this->Position[1] - HEIGHT_UNIT;
        break;
    default:
        break;
    }
}

bool GameObject::move(std::array<float, 2> velocity)
{
    if (this->Position[0] < this->newPosition[0])
    {
        if (this->newPosition[0] - this->Position[0] <= velocity[0])
        {
            this->Position[0] = this->newPosition[0];
            return true;
        }
        else
        {
            this->Position[0] += velocity[0];
            return false;
        }
    }
    //Movement to the left
    if (this->Position[0] > this->newPosition[0])
    {
        if (this->newPosition[0] - this->Position[0] >= -velocity[0])
        {
            this->Position[0] = this->newPosition[0];
            return true;
        }
        else
        {
            this->Position[0] -= velocity[0];
            return false;
        }
    }
    //Movement up
    if (this->Position[1] < this->newPosition[1])
    {
        if (this->newPosition[1] - this->Position[1] <= velocity[1])
        {
            this->Position[1] = this->newPosition[1];
            return true;
        }
        else
        {
            this->Position[1] += velocity[1];
            return false;
        }
    }
    //Movement down
    if (this->Position[1] > this->newPosition[1])
    {
        if (this->newPosition[1] - this->Position[1] >= -velocity[1])
        {
            this->Position[1] = this->newPosition[1];
            return true;
        }
        else
        {
            this->Position[1] -= velocity[1];
            return false;
        }
    }
}

void GameObject::addObserver(const std::shared_ptr<Observer<GameObject*>>& observer)
{
    observers.push_back(observer);
}

void GameObject::removeObserver(const std::shared_ptr<Observer<GameObject*>>& observer)
{
    observers.erase(std::remove_if(observers.begin(), observers.end(),
        [&](const std::shared_ptr<Observer<GameObject*>>& vergleich) {
            return vergleich == observer;
        }));
}

void GameObject::notify()
{
    for (auto& observer : observers)
    {
        observer->update(this);
    }
}