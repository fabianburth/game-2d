#pragma once

#include <string>

#include "GameObject.h"

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


class Player : public GameObject 
{
public:
	bool ready = true;
	bool toggleSprite = false;
	Direction direction = Direction::NONE;
	std::array<float, 2> newPosition;

	Player();
	Player(std::array<float, 2> pos, std::array<float, 4> size, Texture2D sprite);
	void setDirection(Direction direction);
	void move(std::array<float, 2> velocity);
	void swapSprite();
	void calculateMovement();
};