#pragma once

#include "Animator.h"
#include "Player.h"
#include "ResourceManager.h"

class PengoAnimator: public Animator, public Observer<Player*>
{
public:
	Player* pengo;
	const float PUSH_DURATION; 
	const float WALK_ANIMATION_DURATION;
	void (PengoAnimator::* currentAnimation)();

	PengoAnimator(Player* pengo, float pushDuration, float walkAnimationDuration);
	void update(Player* pengo);
	void animate(float dt);
	void stand();
	void walk();
	void pushBlock();
	void breakBlock();
};