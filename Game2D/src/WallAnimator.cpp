#include "WallAnimator.h"

WallAnimator::WallAnimator(Wall* BottomWall, Wall* TopWall, Wall* LeftWall, Wall* RightWall, float wobbleDuration)
	:WOBBLE_DURATION{wobbleDuration}
{
	BottomWall->registerObserver(this);
	TopWall->registerObserver(this);
	RightWall->registerObserver(this);
	LeftWall->registerObserver(this);
}

WallAnimator::~WallAnimator()
{
}

void WallAnimator::update(Wall* s)
{
	if (s->state == WallState::WOBBLY)
	{
		this->wall = s;
		currentAnimation = &WallAnimator::wobble;
	}
}

void WallAnimator::animate(float dt)
{
	if (currentAnimation != nullptr)
	{
		(*this.*currentAnimation)();
		currentAnimationDuration += dt;
	}
}

void WallAnimator::wobble()
{
	Texture2D wobblySprite0;
	Texture2D wobblySprite1;
	Texture2D sprite;
	if (wall->side == WallSide::TOP || wall->side == WallSide::BOTTOM)
	{
		sprite = ResourceManager::GetTexture("wallBT");
		wobblySprite0 = ResourceManager::GetTexture("wallBT_00");
		wobblySprite1 = ResourceManager::GetTexture("wallBT_01");
	}
	else if (wall->side == WallSide::LEFT || wall->side == WallSide::RIGHT)
	{
		sprite = ResourceManager::GetTexture("wallLR");
		wobblySprite0 = ResourceManager::GetTexture("wallLR_00");
		wobblySprite1 = ResourceManager::GetTexture("wallLR_01");
	}

	if (currentAnimationDuration == 0)
	{
		wall->setSprite(wobblySprite0);
	}
	else if (currentAnimationDuration >= (1.0f / 5.0f) * WOBBLE_DURATION && currentAnimationDuration < (2.0f / 5.0f) * WOBBLE_DURATION)
	{
		wall->setSprite(wobblySprite1);
	}
	else if (currentAnimationDuration >= (2.0f / 5.0f) * WOBBLE_DURATION && currentAnimationDuration < (3.0f / 5.0f) * WOBBLE_DURATION)
	{
		wall->setSprite(wobblySprite0);
	}
	else if (currentAnimationDuration >= (3.0f / 5.0f) * WOBBLE_DURATION && currentAnimationDuration < (4.0f / 5.0f) * WOBBLE_DURATION)
	{
		wall->setSprite(wobblySprite1);
	}
	else if (currentAnimationDuration >= WOBBLE_DURATION)
	{
		wall->setSprite(sprite);
		wall->setState(WallState::SOLID);
		currentAnimation = nullptr;
		currentAnimationDuration = 0.0f;
	}
}
