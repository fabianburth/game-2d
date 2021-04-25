#include "Player.h"
#include "ResourceManager.h"

Player::Player()
{
}

Player::Player(std::array<float, 2> pos, std::array<float, 4> size, Texture2D sprite)
    :GameObject{ pos, size, sprite }, ready{ true }, newPosition{ pos[0], pos[1] }
{
}

void Player::setDirection(Direction direction)
{
    if (this->direction != direction)
    {
        this->direction = direction;
    }
}

void Player::move(std::array<float, 2> velocity)
{
	if (this->Position[0] < this->newPosition[0])
        {
            if (this->newPosition[0] - this->Position[0] <= velocity[0]) 
            {
                this->Position[0] = this->newPosition[0];
                this->ready = true;
            }
            else
                this->Position[0] += velocity[0];
        }
        //Movement to the left
        if (this->Position[0] > this->newPosition[0])
        {
            if (this->newPosition[0] - this->Position[0] >= -velocity[0]) 
            {
                this->Position[0] = this->newPosition[0];
                this->ready = true;
            }
            else
                this->Position[0] -= velocity[0];
        }
        //Movement up
        if (this->Position[1] < this->newPosition[1])
        {
            if (this->newPosition[1] - this->Position[1] <= velocity[1])
            {
                this->Position[1] = this->newPosition[1];
                this->ready = true;
            }
            else
                this->Position[1] += velocity[1];
        }
        //Movement down
        if (this->Position[1] > this->newPosition[1])
        {
            if (this->newPosition[1] - this->Position[1] >= -velocity[1])
            {
                this->Position[1] = this->newPosition[1];
                this->ready = true;
            }
            else
                this->Position[1] -= velocity[1];
        }
}

void Player::swapSprite()
{
    if (toggleSprite)
    {
        toggleSprite = false;
        this->Sprite = ResourceManager::GetTexture("pengo" + stringDirection(this->direction));
    }
    else
    {
        toggleSprite = true;
        this->Sprite = ResourceManager::GetTexture("pengoMove" + stringDirection(this->direction));
    }
}

void Player::calculateMovement()
{
    switch (this->direction)
    {
    case Direction::RIGHT:
        this->newPosition[0] = this->Position[0] + WIDTH_UNIT;
        this->ready = false;
        break;
    case Direction::LEFT:
        this->newPosition[0] = this->Position[0] - WIDTH_UNIT;
        this->ready = false;
        break;
    case Direction::UP:
        this->newPosition[1] = this->Position[1] + HEIGHT_UNIT;
        this->ready = false;
        break;
    case Direction::DOWN:
        this->newPosition[1] = this->Position[1] - HEIGHT_UNIT;
        this->ready = false;
        break;
    default:
        break;
    }
}

