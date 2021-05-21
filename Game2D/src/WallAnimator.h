#pragma once

#include "Animator.h"
#include "ResourceManager.h"
#include "Wall.h"

class WallAnimator : public Animator<Wall>
{
public:
	Wall* wall = 0;
	const float WOBBLE_DURATION = 0.0f;
	void (WallAnimator::* currentAnimation)() = nullptr;

	WallAnimator(Wall* BottomWall, Wall* TopWall, Wall* LeftWall, Wall* RightWall, float wobbleDuration);
	~WallAnimator();
	void update(Wall* s) override;
	void animate(float dt) override;
	void wobble();
};
