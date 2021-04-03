#include "Player.h"

Player::Player(std::array<float, 2> pos, std::array<float, 4> size, Texture2D sprite)
	:GameObject{pos, size, sprite}, newPosition{pos[0], pos[1]}
{
}
