#pragma once

#include "../Animator.h"
#include "ResourceManager.h"
#include "../Model/Wall.h"

class WallAnimator : public Animator<Wall>
{
public:
	Wall* wall = nullptr;
	Texture2D sprite;
	Texture2D standardSprite;
	Texture2D wobblySprite0;
	Texture2D wobblySprite1;
	const float WOBBLE_DURATION = 0.0f;
	void (WallAnimator::* currentAnimation)() = nullptr;

	WallAnimator(Wall* wall, float wobbleDuration);
	~WallAnimator();
	void update(Wall* s) override;
	void animate(float dt) override;
	void wobble();
};
