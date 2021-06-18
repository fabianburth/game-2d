#include "BlockAnimator.h"

BlockAnimator::BlockAnimator(float breakingDuration, float flashingDuration, Block* block)
	:BREAKING_DURATION(breakingDuration), FLASHING_DURATION(flashingDuration)
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
	switch (brick->state)
	{
	case(BlockState::BREAKING):
		currentAnimationDuration = 0;
		currentAnimation = &BlockAnimator::destroyIceblock;
		break;
	case(BlockState::SPAWNING):
		currentAnimationDuration = 0;
		currentAnimation = &BlockAnimator::spawnEnemy;
		break;
	case(BlockState::FLASHING):
		currentAnimationDuration = 0;
		currentAnimation = &BlockAnimator::flash;
		break;
	case(BlockState::BROKEN):
		currentAnimationDuration = 0;
		currentAnimation = nullptr;
		break;
	default:
		break;
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

void BlockAnimator::spawnEnemy()
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

		this->brick->containedEnemy->setState(EnemyState::SPAWNING);
	}
}

void BlockAnimator::flash()
{
	if (currentAnimationDuration == 0)
	{
		this->brick->sprite = ResourceManager::GetTexture("iceblockGreen");
	}
	else if (currentAnimationDuration >= (1.0f / 5.0f) * FLASHING_DURATION && currentAnimationDuration < (2.0f / 5.0f) * FLASHING_DURATION)
	{
		this->brick->sprite = ResourceManager::GetTexture("iceblock");
	}
	else if (currentAnimationDuration >= (2.0f / 5.0f) * FLASHING_DURATION && currentAnimationDuration < (3.0f / 5.0f) * FLASHING_DURATION)
	{
		this->brick->sprite = ResourceManager::GetTexture("iceblockGreen");
	}
	else if (currentAnimationDuration >= (3.0f / 5.0f) * FLASHING_DURATION && currentAnimationDuration < (4.0f / 5.0f) * FLASHING_DURATION)
	{
		this->brick->sprite = ResourceManager::GetTexture("iceblock");
	}
	else if (currentAnimationDuration >= (4.0f / 5.0f) * FLASHING_DURATION && currentAnimationDuration < FLASHING_DURATION)
	{
		this->brick->sprite = ResourceManager::GetTexture("iceblockGreen");
	}
	else if (currentAnimationDuration >= FLASHING_DURATION)
	{
		this->brick->sprite = ResourceManager::GetTexture("iceblock");
		currentAnimationDuration = 0.0f;
		currentAnimation = nullptr;
		this->brick->state = BlockState::SOLID;
	}
}
