#pragma once

#include "GameObject.h"

class Player : public GameObject 
{
public:
	std::array<float, 2> newPosition;

	Player(std::array<float, 2> pos, std::array<float, 4> size, Texture2D sprite);
};