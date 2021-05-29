#pragma once

#include "Animator.h"
#include "GameObject.h"
#include "Block.h"
#include "ResourceManager.h"
#include <any>

class BlockAnimator : public Animator<GameObject>
{
public:
	Block* brick = 0;
	const float BREAKING_DURATION = 0.0f;
	void (BlockAnimator::* currentAnimation)() = nullptr;

	BlockAnimator(float breakingDuration, Block* block);
	~BlockAnimator();
	void update(GameObject* s);
	void animate(float dt);
	void destroyIceblock();
};