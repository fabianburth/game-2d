#include "EnemyAnimator.h"


EnemyAnimator::EnemyAnimator(Enemy* enemy, float walkAnimationDuration)
	:enemy(enemy), WALK_ANIMATION_DURATION(walkAnimationDuration), currentAnimation(&EnemyAnimator::walk)
{
	enemy->registerObserver(this);
}

EnemyAnimator::~EnemyAnimator()
{
}

void EnemyAnimator::animate(float dt)
{
	(*this.*currentAnimation)();
	currentAnimationDuration += dt;
}

void EnemyAnimator::update(GameObject* s)
{
	Enemy* enemy = dynamic_cast<Enemy*>(s);
	switch (enemy->state)
	{
	case(EnemyState::WANDERING):
	case(EnemyState::CHASING):
		currentAnimationDuration = 0.0f;
		currentAnimation = &EnemyAnimator::walk;
		break;
	case(EnemyState::BREAKING):
		currentAnimationDuration = 0.0f;
		currentAnimation = &EnemyAnimator::breakBlock;
	}
}

void EnemyAnimator::walk()
{
	std::string animationType;
	if (enemy->state == EnemyState::CHASING)
		animationType = "Boxer";
	else
		animationType = "Move";

	if (currentAnimationDuration == 0.0f)
	{
		enemy->sprite = ResourceManager::GetTexture("enemy" + animationType + stringDirection(enemy->direction) + "00");
	}
	else if (currentAnimationDuration > 0.5f * WALK_ANIMATION_DURATION && currentAnimationDuration <= WALK_ANIMATION_DURATION)
	{
		enemy->sprite = ResourceManager::GetTexture("enemy" + animationType + stringDirection(enemy->direction) + "01");
	}
	else if (currentAnimationDuration > WALK_ANIMATION_DURATION)
	{
		currentAnimationDuration = 0.0f;
		enemy->sprite = ResourceManager::GetTexture("enemy" + animationType + stringDirection(enemy->direction) + "00");
	}
}

void EnemyAnimator::breakBlock()
{
	std::string animationType;
	if (enemy->state == EnemyState::BREAKING)
		animationType = "Boxer";
	else
		animationType = "Move";

	enemy->ready = false;
	if (currentAnimationDuration == 0.0f)
	{
		enemy->sprite = ResourceManager::GetTexture("enemy" + animationType + stringDirection(enemy->direction) + "00");
	}
	else if (currentAnimationDuration > 0.25f * WALK_ANIMATION_DURATION && currentAnimationDuration <= 0.5f * WALK_ANIMATION_DURATION)
	{
		enemy->sprite = ResourceManager::GetTexture("enemy" + animationType + stringDirection(enemy->direction) + "01");
	}
	else if (currentAnimationDuration > 0.5f * WALK_ANIMATION_DURATION && currentAnimationDuration <= 0.75f * WALK_ANIMATION_DURATION)
	{
		enemy->sprite = ResourceManager::GetTexture("enemy" + animationType + stringDirection(enemy->direction) + "00");
	}
	else if (currentAnimationDuration > 0.75f * WALK_ANIMATION_DURATION && currentAnimationDuration <= WALK_ANIMATION_DURATION)
	{
		enemy->sprite = ResourceManager::GetTexture("enemy" + animationType + stringDirection(enemy->direction) + "01");
	}
	else if (currentAnimationDuration > WALK_ANIMATION_DURATION)
	{
		enemy->sprite = ResourceManager::GetTexture("enemy" + animationType + stringDirection(enemy->direction) + "00");
		enemy->setState(EnemyState::CHASING);
		enemy->setPositionToMoveTo();
	}
}
