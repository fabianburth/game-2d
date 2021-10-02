#pragma once

#include <string>
#include <vector>

#include "GameObject.h"
#include "../util.h"

class Player : public GameObject
{
public:
	Direction direction = Direction::NONE;
	PengoState state = PengoState::STAND;
	std::array<float, 2> velocity, positionToMoveTo;
	bool ready;
	int lives = 1;

	static constexpr float WALKING_DURATION = 0.25f;
	static constexpr float PUSHING_DURATION = 0.5f;
	static constexpr float BREAKING_BLOCK_DURATION = 0.5f;
	float walkingFor = 0.0f;
	float pushingFor = 0.0f;
	float breakingBlockFor = 0.0f;

	Player();
	Player(std::array<float, 2> pos, std::array<float, 2> velocity);

	void setDirection(Direction direction);
	void setState(PengoState state);
	void setPositionToMoveTo();
	void move(float deltaTime);
};