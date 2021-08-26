#pragma once
#include "GameObject.h"

enum class EnemyState
{
	CHASING,
	WANDERING,
	BREAKING,
	STUNNED,
	SPAWNING,
	INITIAL_SPAWNING,
	NONE
};

class Enemy : public GameObject
{
public:
	Direction direction;
	EnemyState state;
	std::string baseType;
	std::array<float, 2> velocity, positionToMoveTo;
	bool ready;

	Enemy();
	Enemy(std::array<float, 2> pos, Texture2D sprite, std::array<float, 2> velocity, Direction direction, EnemyState state, std::string baseType, bool ready);

	void setDirection(Direction direction);
	void setState(EnemyState state);
	void setPositionToMoveTo();
	void move(float deltaTime);

	// Auxiliary method which generates a vector containing probabilities for the possible directions
	// @param directions: A vector containing all possible directions for the enemy to move to
	// @return: A vector containing a probability for each direction in the direction vector
	std::vector<int> getProbabilityArray(std::vector<Direction> directions);

};