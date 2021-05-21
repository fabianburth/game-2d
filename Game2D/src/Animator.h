#pragma once

#include "Observer.h"
#include "GameObject.h"

class Animator: public Observer<GameObject>
{
public:
	float currentAnimationDuration = 0.0f;

	//virtual void update(GameObject gameObject) = 0;
	virtual void animate(float dt) = 0;
};