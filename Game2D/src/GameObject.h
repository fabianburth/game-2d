#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>

#include "texture.h"
#include "spriterenderer.h"


// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject
{
public:
    // object state
    std::array<float,2>   Position, Velocity;
    std::array<float, 4> Size;
    std::array<float,3>   Color;
    bool        IsSolid;
    bool        Destroyed;
    // render state
    Texture2D   Sprite;
    // constructor(s)
    GameObject();
    GameObject(std::array<float, 2> pos, std::array<float, 4> size, Texture2D sprite, std::array<float, 3> color = { 1.0f, 1.0f, 1.0f }, std::array<float, 2> velocity = { 0.0f, 0.0f });
    // draw sprite
    virtual void Draw(SpriteRenderer& renderer);
};

#endif