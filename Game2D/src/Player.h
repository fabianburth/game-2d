#pragma once

#include "GameObject.h"

class Player : public GameObject 
{
public:
	bool ready;
	std::array<float, 2> newPosition;

	Player();
	Player(std::array<float, 2> pos, std::array<float, 4> size, Texture2D sprite);
	void move(std::array<float, 2> velocity);
	void calcMoveRight();
	void calcMoveLeft();
	void calcMoveUp();
	void calcMoveDown();

};