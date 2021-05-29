#pragma once
#include "GameObject.h"

enum class EnemyState
{
	CHASING,
	WANDERING,
	BREAKING
};

class Enemy : public GameObject
{
public:
	Direction direction;
	EnemyState state;
	std::array<float, 2> velocity, positionToMoveTo;
	bool ready = true;

	Enemy();
	Enemy(std::array<float, 2> pos, Texture2D sprite, std::array<float, 2> velocity, Direction direction, EnemyState state);

	void setDirection(Direction direction);
	void setState(EnemyState state);
	void setPositionToMoveTo();
	void move(float deltaTime);

};