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

class Player : public GameObject
{
public:
	Direction direction = Direction::NONE;
	PengoState state = PengoState::STAND;
	std::array<float, 2> velocity, positionToMoveTo;
	bool ready;
	bool toggleSprite;

	Player();
	Player(std::array<float, 2> pos, Texture2D sprite, std::array<float, 2> velocity);

	//virtual void registerObserver(const std::shared_ptr<Observer>& observer);
	//virtual void removeObserver(const std::shared_ptr<Observer>& observer);
	//virtual void notifyObservers();

	void setDirection(Direction direction);
	void setState(PengoState state);
	void setPositionToMoveTo();
	void move(float deltaTime);
	void swapSprite();

//private:
//	std::vector<std::shared_ptr<Observer>> observers;
};