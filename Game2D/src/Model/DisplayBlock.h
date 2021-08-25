#pragma once

#include <array>
#include "../View/Texture.h"

class DisplayBlock
{
public:
	//bottom left position of the block
	//  |-----|
	//  |     |
	//  x-----|
	std::array<float, 2> position;
	std::array<float, 4> size;
	Texture2D sprite;

	DisplayBlock();
	DisplayBlock(std::array<float, 2> position, std::array<float, 4> size, Texture2D sprite);
};
