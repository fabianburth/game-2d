#pragma once

#include <string>
#include <vector>

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

enum class PengoState
{
	STAND,
	WALK,
	PUSH
};

static std::string stringState(PengoState state)
{
	switch (state)
	{
	case PengoState::STAND:
		return "Stand";
		break;
	case PengoState::WALK:
		return "Walk";
		break;
	case PengoState::PUSH:
		return "Push";
		break;
	default:
		return "";
		break;
	}
}

class Player : public GameObject, public Subject<Player*>
{
public:
	bool ready = true;
	bool toggleSprite = false;
	Direction direction = Direction::NONE;
	PengoState state = PengoState::STAND;
	std::array<float, 2> newPosition;

	Player();
	Player(std::array<float, 2> pos, std::array<float, 4> size, Texture2D sprite);

	virtual void addObserver(const std::shared_ptr<Observer<Player*>>& observer);
	virtual void removeObserver(const std::shared_ptr<Observer<Player*>>& observer);
	virtual void notify();

	void setDirection(Direction direction);
	void setState(PengoState state);
	void move(std::array<float, 2> velocity);
	void swapSprite();
	void calculateMovement();

private:
	std::vector<std::shared_ptr<Observer<Player*>>> observers;
};