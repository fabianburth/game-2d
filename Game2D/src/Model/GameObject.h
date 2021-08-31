#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../Constants.h"
#include <GL/glew.h>
#include <memory>
#include <vector>
#include <array>
#include <string>

#include "../View/Texture.h"
#include "../Subject.h"

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

static Direction oppositeDirection(Direction direction)
{
	switch (direction)
	{
	case Direction::RIGHT:
		return Direction::LEFT;
		break;
	case Direction::LEFT:
		return Direction::RIGHT;
		break;
	case Direction::UP:
		return Direction::DOWN;
		break;
	case Direction::DOWN:
		return Direction::UP;
		break;
	case Direction::NONE:
		return Direction::NONE;
		break;
	}
}

// TODO
// Make a subclass "Blocks" of GameObject and implement replace [bool Destroyed] with a enum class to clean up the observer pattern
// Add the observer upon creation of the objects instead of in the Game class
// Add another Animator class for the Wall

//enum class BrickState
//{
//    SOLID,
//    BREAKING,
//    BROKEN
//};

// Check whether observer pattern can be programmed against GameObject interface
// Clean the Block class up

// Container object for holding all state relevant for a single
// game object entity. Each object in the game likely needs the
// minimal of state as described within GameObject.
class GameObject: public Subject<GameObject>
{
public:
    // object state
    std::array<float,2> position;
	std::array<float, 4> size;
    //std::array<float, 4> size;
    //std::array<float,3>   color;
    //bool        IsUnbreakable = true;
    //bool        Destroyed = false;
    // render state
    Texture2D   sprite;
    // constructor(s)
    GameObject();
	GameObject(std::array<float, 2> pos, Texture2D sprite, std::array<float, 4> size = { 1.0f, 1.0f, 0.0f, 0.0f });
    //GameObject(std::array<float, 2> pos, std::array<float, 4> size, Texture2D sprite, std::array<float, 3> color = { 1.0f, 1.0f, 1.0f }, std::array<float, 2> velocity = { 0.0f, 0.0f });

    void registerObserver (Observer<GameObject>* o) override;
    void removeObserver(Observer<GameObject>* o) override;
    void notifyObservers() override;

    // --void destroy();
    //void yeet(Direction d, int stepRange);
	//virtual void move() = 0;
	//virtual void calculateMovement() = 0;
	// 
    // draw sprite
    // --virtual void Draw(SpriteRenderer& renderer);

private:
    std::vector<Observer<GameObject>*> observers;
};

#endif