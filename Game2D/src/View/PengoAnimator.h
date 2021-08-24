#pragma once

#include "../Animator.h"
#include "../Model/Player.h"
#include "ResourceManager.h"
#include <any>

class PengoAnimator: public Animator<GameObject>
{
public:
	Player* pengo;
	const float PUSH_DURATION; 
	const float WALK_ANIMATION_DURATION;
	void (PengoAnimator::* currentAnimation)();

	PengoAnimator(Player* pengo, float pushDuration, float walkAnimationDuration);
	~PengoAnimator();
	void update(GameObject* s) override;
	void animate(float dt);
	void stand();
	void walk();
	void pushBlock();
	void breakBlock();
};