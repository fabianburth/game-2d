#pragma once
#include "GameObject.h"

enum class EnemyType
{
	CHASING,
	WANDERING
};

enum class EnemyState
{
	BREAKING,
	STUNNED,
	SPAWNING,
	INITIAL_SPAWNING,
	NONE
};

class Enemy : public GameObject
{
public:
    unsigned int id;
	Direction direction;
	EnemyState state;
	EnemyType type;
	std::array<float, 2> velocity, positionToMoveTo;
	bool ready;

	static constexpr float BREAKING_BLOCK_DURATION = 0.5f;
	static constexpr float STUNN_DURATION = 3.0f;
	static constexpr float SPAWN_DURATION = 1.5f;
	float breakingBlockFor = 0.0f;
	float stunnedFor = 0.0f;
	float spawningFor = 0.0f;

	Enemy();
	Enemy(std::array<float, 2> pos, std::array<float, 2> velocity, Direction direction, EnemyState state, EnemyType type, bool ready);

	void setDirection(Direction direction);
	void setState(EnemyState state);
	void setType(EnemyType type);
	void setPositionToMoveTo();
	void move(float deltaTime);

	/** Auxiliary method which generates a vector containing probabilities for the possible directions
	* @param directions: A vector containing all possible directions for the enemy to move to
	* @return: A vector containing a probability for each direction in the direction vector
	*/
	std::vector<int> getProbabilityArray(std::vector<Direction> directions);

private:
    static unsigned int nextID;

};