#pragma once

#include <string>
#include <vector>

#include "GameObject.h"

enum class PengoState
{
	STAND,
	WALK,
	PUSH,
	BREAK
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
	case PengoState::BREAK:
		return "Break";
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