#pragma once

#include "Animator.h"
#include "GameObject.h"
#include "ResourceManager.h"

class BlockAnimator : public Animator, public Observer<GameObject*>
{
public:
	GameObject* brick = 0;
	const float BREAKING_DURATION = 0.0f;
	void (BlockAnimator::* currentAnimation)() = nullptr;

	BlockAnimator(float breakingDuration);
	void update(GameObject* brick);
	void animate(float dt);
	void destroyIceblock();
};