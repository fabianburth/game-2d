#include "BlockAnimator.h"

BlockAnimator::BlockAnimator(float breakingDuration, Block* block)
	:BREAKING_DURATION(breakingDuration) 
{
	this->brick = block;
	this->brick->registerObserver(this);
}

BlockAnimator::~BlockAnimator()
{
}

void BlockAnimator::update(GameObject* s)
{
	//Block* block = dynamic_cast<Block*>(s);
	if (brick->state != BlockState::BROKEN)
	{
		//this->brick = block;
		currentAnimation = &BlockAnimator::destroyIceblock;
	}
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
		this->brick->sprite = ResourceManager::GetTexture("iceblockBreaking0");
	}
	else if (currentAnimationDuration >= (1.0f / 4.0f) * BREAKING_DURATION && currentAnimationDuration < (2.0f / 4.0f) * BREAKING_DURATION)
	{
		this->brick->sprite = ResourceManager::GetTexture("iceblockBreaking1");
	}
	else if (currentAnimationDuration >= (2.0f / 4.0f) * BREAKING_DURATION && currentAnimationDuration < (3.0f / 4.0f) * BREAKING_DURATION)
	{
		this->brick->sprite = ResourceManager::GetTexture("iceblockBreaking2");
	} 
	else if (currentAnimationDuration >= (3.0f / 4.0f) * BREAKING_DURATION && currentAnimationDuration < BREAKING_DURATION)
	{
		this->brick->sprite = ResourceManager::GetTexture("iceblockBreaking3");
	}
	else if (currentAnimationDuration >= BREAKING_DURATION)
	{
		currentAnimationDuration = 0.0f;
		currentAnimation = nullptr;
		this->brick->state = BlockState::BROKEN;
	}
}
