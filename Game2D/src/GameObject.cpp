#include "gameobject.h"


GameObject::GameObject()
    : Position({ 0.0f, 0.0f }), Size({ 1.0f, 1.0f }), Velocity({ 0.0f, 0.0f }), Color({ 1.0f, 1.0f, 1.0f }), Sprite(), IsSolid(false), Destroyed(false) { }

GameObject::GameObject(std::array<float,2> pos, std::array<float, 4> size, Texture2D sprite, std::array<float, 3> color, std::array<float, 2> velocity)
    : Position(pos), Size(size), Velocity(velocity), Color(color), Sprite(sprite), IsSolid(true), Destroyed(false) { }

void GameObject::destroy()
{
    notify();
}

void GameObject::Draw(SpriteRenderer& renderer)
{
    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Color);
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