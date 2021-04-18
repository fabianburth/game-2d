#include "Player.h"

Player::Player()
{
}

Player::Player(std::array<float, 2> pos, std::array<float, 4> size, Texture2D sprite)
    :GameObject{ pos, size, sprite }, ready{ true }, newPosition{ pos[0], pos[1] }
{
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

void Player::calcMoveRight()
{
    // if ((-1.0f + 0.5f * WIDTH_UNIT) + this->Position[0] + WIDTH_UNIT < 1.0f - 0.5f * WIDTH_UNIT)
    {
        this->newPosition[0] = this->Position[0] + WIDTH_UNIT;
        this->ready = false;
    }

}

void Player::calcMoveLeft()
{
    //if ((-1.0f + 0.5f * WIDTH_UNIT) + this->Position[0] - WIDTH_UNIT >= -1.0f + 0.5f * WIDTH_UNIT) 
    {
        this->newPosition[0] = this->Position[0] - WIDTH_UNIT;
        this->ready = false;
    }
}

void Player::calcMoveUp()
{
    //if ((-1.0f + 0.5f * HEIGHT_UNIT) + this->Position[1] + HEIGHT_UNIT < 1.0f - 2 * HEIGHT_UNIT - 0.5f * HEIGHT_UNIT) 
    {
        this->newPosition[1] = this->Position[1] + HEIGHT_UNIT;
        this->ready = false;
    }
}

void Player::calcMoveDown()
{
    //if ((-1.0f + 0.5f * HEIGHT_UNIT) + this->Position[1] - HEIGHT_UNIT >= -1.0f + 0.5f * HEIGHT_UNIT) 
    {
        this->newPosition[1] = this->Position[1] - HEIGHT_UNIT;
        this->ready = false;
    }
}

