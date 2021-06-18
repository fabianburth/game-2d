#pragma once

#include "Animator.h"
#include "Enemy.h"
#include "ResourceManager.h"
#include <string>

class EnemyAnimator : public Animator<GameObject>
{
public:
	Enemy* enemy;
	const float WALK_ANIMATION_DURATION;
	const float STUNNED_ANIMATION_DURATION;
	const float SPAWNING_ANIMATION_DURATION;
	void (EnemyAnimator::* currentAnimation)() = nullptr;

	EnemyAnimator(Enemy* enemy, float walkAnimationDuration, float stunnedAnimationDuration, float spawningAnimationDuration);
	~EnemyAnimator();
	void update(GameObject* s) override;
	void animate(float dt);
	void walk();
	void breakBlock();
	void stunned();
	void spawning();
	void spawningFromBlock();
};