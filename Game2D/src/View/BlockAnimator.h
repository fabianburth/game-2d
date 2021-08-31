#pragma once

#include "../Animator.h"
#include "../Model/GameObject.h"
#include "../Model/Block.h"
#include "ResourceManager.h"
#include <any>

class BlockAnimator : public Animator<GameObject>
{
public:
	Block* block = nullptr;
	Texture2D sprite;
	const float BREAKING_DURATION = 0.0f;
	const float FLASHING_DURATION = 0.0f;
	void (BlockAnimator::* currentAnimation)() = nullptr;

	BlockAnimator(Block *block, float flashingDuration, float breakingDuration, Texture2D sprite);
	~BlockAnimator();
	void update(GameObject* s);
	void animate(float dt);
	void destroyIceblock();
	void spawnEnemy();
	void flash();
};