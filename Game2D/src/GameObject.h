#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>
#include <vector>

#include "texture.h"
#include "spriterenderer.h"
#include "Subject.h"

enum class Direction
{
	RIGHT,
	LEFT,
	UP,
	DOWN,
	NONE
};

static std::string stringDirection(Direction direction)
{
	switch (direction)
	{
	case Direction::RIGHT:
		return "Right";
		break;
	case Direction::LEFT:
		return "Left";
		break;
	case Direction::UP:
		return "Up";
		break;
	case Direction::DOWN:
		return "Down";
		break;
	case Direction::NONE:
		return "None";
		break;
	default:
		return "";
		break;
	}
}

//TODO
//Make a subclass "Bricks" of GameObject and implement replace [bool Destroyed] with a enum class to clean up the observer pattern

//enum class BrickState
//{
//    SOLID,
//    BREAKING,
//    BROKEN
//};

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject: public Subject<GameObject*>
{
public:
    // object state
    std::array<float,2>   Position, Velocity;
	std::array<float, 2> newPosition;
    std::array<float, 4> Size;
    std::array<float,3>   Color;
    bool        IsSolid = true;
    bool        Destroyed = false;
    // render state
    Texture2D   Sprite;
    // constructor(s)
    GameObject();
    GameObject(std::array<float, 2> pos, std::array<float, 4> size, Texture2D sprite, std::array<float, 3> color = { 1.0f, 1.0f, 1.0f }, std::array<float, 2> velocity = { 0.0f, 0.0f });

    virtual void addObserver (const std::shared_ptr<Observer<GameObject*>>& observer);
    virtual void removeObserver(const std::shared_ptr<Observer<GameObject*>>& observer);
    virtual void notify();

    void destroy();
    void yeet(Direction d, int stepRange);
	bool move(std::array<float, 2> velocity);
	void calculateMovement(Direction d);
    // draw sprite
    virtual void Draw(SpriteRenderer& renderer);

private:
    std::vector<std::shared_ptr<Observer<GameObject*>>> observers;
};

#endif