#include "BlockAnimator.h"

BlockAnimator::BlockAnimator(float breakingDuration)
	:BREAKING_DURATION(breakingDuration){}

void BlockAnimator::update(GameObject* brick)
{
	if (!brick->Destroyed)
		this->brick = brick;
		currentAnimation = &BlockAnimator::destroyIceblock;
}

void BlockAnimator::animate(float dt)
{
	if (currentAnimation != nullptr)
	{
		(*this.*currentAnimation)();
		currentAnimationDuration += dt;
	}
}

void BlockAnimator::destroyIceblock()
{
	if (currentAnimationDuration == 0)
	{
		this->brick->Sprite = ResourceManager::GetTexture("iceblockBreaking0");
	}
	else if (currentAnimationDuration >= (1.0f / 4.0f) * BREAKING_DURATION && currentAnimationDuration < (2.0f / 4.0f) * BREAKING_DURATION)
	{
		this->brick->Sprite = ResourceManager::GetTexture("iceblockBreaking1");
	}
	else if (currentAnimationDuration >= (2.0f / 4.0f) * BREAKING_DURATION && currentAnimationDuration < (3.0f / 4.0f) * BREAKING_DURATION)
	{
		this->brick->Sprite = ResourceManager::GetTexture("iceblockBreaking2");
	} 
	else if (currentAnimationDuration >= (3.0f / 4.0f) * BREAKING_DURATION && currentAnimationDuration < BREAKING_DURATION)
	{
		this->brick->Sprite = ResourceManager::GetTexture("iceblockBreaking3");
	}
	else if (currentAnimationDuration >= BREAKING_DURATION)
	{
		this->brick->Destroyed = true;
		currentAnimationDuration = 0.0f;
		currentAnimation = nullptr;
	}
}
