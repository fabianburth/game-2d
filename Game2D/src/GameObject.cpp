#include "gameobject.h"


GameObject::GameObject()
    : Position({ 0.0f, 0.0f }), Size({ 1.0f, 1.0f }), Velocity({ 0.0f, 0.0f }), Color({ 1.0f, 1.0f, 1.0f }), Sprite(), IsSolid(false), Destroyed(false) { }

GameObject::GameObject(std::array<float,2> pos, std::array<float, 2> size, Texture2D sprite, std::array<float, 3> color, std::array<float, 2> velocity)
    : Position(pos), Size(size), Velocity(velocity), Color(color), Sprite(sprite), IsSolid(false), Destroyed(false) { }

void GameObject::Draw(SpriteRenderer& renderer)
{
    renderer.DrawSprite(this->Sprite, this->Position, this->Size, this->Color);
}