#include "EnemyAnimator.h"


EnemyAnimator::EnemyAnimator(Enemy* enemy, float walkAnimationDuration, float stunnedAnimation)
	:enemy(enemy), WALK_ANIMATION_DURATION(walkAnimationDuration), STUNNED_ANIMATION(stunnedAnimation), currentAnimation(&EnemyAnimator::walk)
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
		break;
	case(EnemyState::STUNNED):
		currentAnimationDuration = 0.0f;
		currentAnimation = &EnemyAnimator::stunned;
		break;
	}
}

void EnemyAnimator::walk()
{
	if (currentAnimationDuration == 0.0f)
	{
		enemy->sprite = ResourceManager::GetTexture("enemy" + enemy->baseType + stringDirection(enemy->direction) + "00");
	}
	else if (currentAnimationDuration > 0.5f * WALK_ANIMATION_DURATION && currentAnimationDuration <= WALK_ANIMATION_DURATION)
	{
		enemy->sprite = ResourceManager::GetTexture("enemy" + enemy->baseType + stringDirection(enemy->direction) + "01");
	}
	else if (currentAnimationDuration > WALK_ANIMATION_DURATION)
	{
		currentAnimationDuration = 0.0f;
		enemy->sprite = ResourceManager::GetTexture("enemy" + enemy->baseType + stringDirection(enemy->direction) + "00");
	}
}

void EnemyAnimator::breakBlock()
{
	enemy->ready = false;
	if (currentAnimationDuration == 0.0f)
	{
		enemy->sprite = ResourceManager::GetTexture("enemy" + enemy->baseType + stringDirection(enemy->direction) + "00");
	}
	else if (currentAnimationDuration > 0.25f * WALK_ANIMATION_DURATION && currentAnimationDuration <= 0.5f * WALK_ANIMATION_DURATION)
	{
		enemy->sprite = ResourceManager::GetTexture("enemy" + enemy->baseType + stringDirection(enemy->direction) + "01");
	}
	else if (currentAnimationDuration > 0.5f * WALK_ANIMATION_DURATION && currentAnimationDuration <= 0.75f * WALK_ANIMATION_DURATION)
	{
		enemy->sprite = ResourceManager::GetTexture("enemy" + enemy->baseType + stringDirection(enemy->direction) + "00");
	}
	else if (currentAnimationDuration > 0.75f * WALK_ANIMATION_DURATION && currentAnimationDuration <= WALK_ANIMATION_DURATION)
	{
		enemy->sprite = ResourceManager::GetTexture("enemy" + enemy->baseType + stringDirection(enemy->direction) + "01");
	}
	else if (currentAnimationDuration > WALK_ANIMATION_DURATION)
	{
		enemy->sprite = ResourceManager::GetTexture("enemy" + enemy->baseType + stringDirection(enemy->direction) + "00");
		enemy->setState(EnemyState::CHASING);
		enemy->setPositionToMoveTo();
	}
}

void EnemyAnimator::stunned()
{
	enemy->ready = false;
	if (currentAnimationDuration == 0.0f)
	{
		enemy->sprite = ResourceManager::GetTexture("enemyStunnedRight");
	}
	else if (currentAnimationDuration > (1.0f / 12.0f) * STUNNED_ANIMATION && currentAnimationDuration <= (2.0f / 12.0f) * STUNNED_ANIMATION)
	{
		enemy->sprite = ResourceManager::GetTexture("enemyStunnedLeft");
	}
	else if (currentAnimationDuration > (2.0f / 12.0f) * STUNNED_ANIMATION && currentAnimationDuration <= (3.0f / 12.0f) * STUNNED_ANIMATION)
	{
		enemy->sprite = ResourceManager::GetTexture("enemyStunnedRight");
	}
	else if (currentAnimationDuration > (3.0f / 12.0f) * STUNNED_ANIMATION && currentAnimationDuration <= (4.0f / 12.0f) * STUNNED_ANIMATION)
	{
		enemy->sprite = ResourceManager::GetTexture("enemyStunnedLeft");
	}
	else if (currentAnimationDuration > (4.0f / 12.0f) * STUNNED_ANIMATION && currentAnimationDuration <= (5.0f / 12.0f) * STUNNED_ANIMATION)
	{
		enemy->sprite = ResourceManager::GetTexture("enemyStunnedRight");
	}
	else if (currentAnimationDuration > (5.0f / 12.0f) * STUNNED_ANIMATION && currentAnimationDuration <= (6.0f / 12.0f) * STUNNED_ANIMATION)
	{
		enemy->sprite = ResourceManager::GetTexture("enemyStunnedLeft");
	}
	else if (currentAnimationDuration > (6.0f / 12.0f) * STUNNED_ANIMATION && currentAnimationDuration <= (7.0f / 12.0f) * STUNNED_ANIMATION)
	{
		enemy->sprite = ResourceManager::GetTexture("enemyStunnedRight");
	}
	else if (currentAnimationDuration > (7.0f / 12.0f) * STUNNED_ANIMATION && currentAnimationDuration <= (8.0f / 12.0f) * STUNNED_ANIMATION)
	{
		enemy->sprite = ResourceManager::GetTexture("enemyStunnedLeft");
	}
	else if (currentAnimationDuration > (8.0f / 12.0f) * STUNNED_ANIMATION && currentAnimationDuration <= (9.0f / 12.0f) * STUNNED_ANIMATION)
	{
		enemy->sprite = ResourceManager::GetTexture("enemyStunnedRight");
	}
	else if (currentAnimationDuration > (9.0f / 12.0f) * STUNNED_ANIMATION && currentAnimationDuration <= (10.0f / 12.0f) * STUNNED_ANIMATION)
	{
		enemy->sprite = ResourceManager::GetTexture("enemyStunnedLeft");
	}
	else if (currentAnimationDuration > (10.0f / 12.0f) * STUNNED_ANIMATION && currentAnimationDuration <= (11.0f / 12.0f) * STUNNED_ANIMATION)
	{
		enemy->sprite = ResourceManager::GetTexture("enemyStunnedRight");
	}
	else if (currentAnimationDuration > (11.0f / 12.0f) * STUNNED_ANIMATION && currentAnimationDuration <= STUNNED_ANIMATION)
	{
		enemy->sprite = ResourceManager::GetTexture("enemyStunnedLeft");
	}
	else if (currentAnimationDuration > STUNNED_ANIMATION)
	{
		if (enemy->baseType == "boxer")
			enemy->setState(EnemyState::CHASING);
		else
			enemy->setState(EnemyState::WANDERING);

		enemy->sprite = ResourceManager::GetTexture("enemy" + enemy->baseType + stringDirection(enemy->direction) + "00");
		currentAnimationDuration = 0.0f;
		enemy->ready = true;
	}

}
