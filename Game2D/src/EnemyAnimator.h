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
	void (EnemyAnimator::* currentAnimation)();

	EnemyAnimator(Enemy* enemy, float walkAnimationDuration);
	~EnemyAnimator();
	void update(GameObject* s) override;
	void animate(float dt);
	void walk();
	void breakBlock();
};