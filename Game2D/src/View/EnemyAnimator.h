#pragma once

#include "../Animator.h"
#include "../Model/Enemy.h"
#include "ResourceManager.h"
#include <string>

class EnemyAnimator : public Animator<GameObject>
{
public:
	Enemy* enemy;
	Texture2D sprite;
	const float WALK_ANIMATION_DURATION;
	const float STUNNED_ANIMATION_DURATION;
	const float SPAWNING_ANIMATION_DURATION;
	void (EnemyAnimator::* currentAnimation)() = nullptr;

	EnemyAnimator(Enemy *enemy, float walkAnimationDuration, float stunnedAnimationDuration, float spawningAnimationDuration, Texture2D sprite);
	~EnemyAnimator();
	void update(GameObject* s) override;
	void animate(float dt);
	void walk();
	void breakBlock();
	void stunned();
	void spawning();
	void spawningFromBlock();
};