#pragma once

#include <vector>
#include <string>
#include "DisplayBlock.h"
#include "Constants.h"
#include "ResourceManager.h"
#include <ctype.h>

class GameInformation
{
public:
	std::array<float, 2> position;
	int amountDisplayBlocks;
	std::array<float, 4> size;

	std::string text;
	std::vector<DisplayBlock*> displayBlocks;

	GameInformation();
	GameInformation(std::array<float, 2> position, std::array<float, 4> size, int amountDisplayBlocks);

	void show(std::string text);
};
