#include "PengoAnimator.h"

PengoAnimator::PengoAnimator(Player* pengo, float pushDuration, float walkAnimationDuration) 
	: pengo(pengo), PUSH_DURATION(pushDuration), WALK_ANIMATION_DURATION(walkAnimationDuration), currentAnimation(&PengoAnimator::stand) { }

void PengoAnimator::animate(float dt)
{
	(*this.*currentAnimation)();
	currentAnimationDuration += dt;
}

void PengoAnimator::update(Player* p)
{
	switch (pengo->state)
	{
	case(PengoState::STAND):
		currentAnimationDuration = 0.0f;
		currentAnimation = &PengoAnimator::stand;
		break;
	case(PengoState::WALK):
		currentAnimationDuration = 0.0f;
		currentAnimation = &PengoAnimator::walk;
		break;
	case(PengoState::PUSH):
		currentAnimationDuration = 0.0f;
		push();
		break;
	}
}

void PengoAnimator::stand()
{
	//Last Sprite just stays active
}

void PengoAnimator::walk()
{
	if (currentAnimationDuration == 0)
	{
		pengo->swapSprite();
	}
	else if (currentAnimationDuration >= WALK_ANIMATION_DURATION)
	{
		pengo->setState(PengoState::STAND);
	}
}

void PengoAnimator::push()
{
	if (pengo->direction == Direction::LEFT || pengo->direction == Direction::RIGHT)
	{
		currentAnimation = &PengoAnimator::pushHorizontally;
	}
	else if (pengo->direction == Direction::UP || pengo->direction == Direction::DOWN)
	{
		currentAnimation = &PengoAnimator::pushVertically;
	}
}

void PengoAnimator::pushHorizontally()
{
	pengo->ready = false;
	pengo->Sprite = ResourceManager::GetTexture("pengoPush" + stringDirection(pengo->direction));
	if (currentAnimationDuration >= PUSH_DURATION)
	{
		pengo->Sprite = ResourceManager::GetTexture("pengoPostPush" + stringDirection(pengo->direction));
		pengo->state = PengoState::STAND;
		pengo->ready = true;
	}
}

void PengoAnimator::pushVertically()
{
	pengo->ready = false;
	if (currentAnimationDuration == 0 )
	{
		pengo->Sprite = ResourceManager::GetTexture("pengoPush" + stringDirection(pengo->direction));
	}
	else if (currentAnimationDuration >= (1.0f / 3.0f) * PUSH_DURATION && currentAnimationDuration < (2.0f / 3.0f) * PUSH_DURATION)
	{
		pengo->Sprite = ResourceManager::GetTexture("pengoPush" + stringDirection(pengo->direction) + "Move");
	}
	else if (currentAnimationDuration >= (2.0f / 3.0f) * PUSH_DURATION && currentAnimationDuration < PUSH_DURATION)
	{
		pengo->Sprite = ResourceManager::GetTexture("pengoPush" + stringDirection(pengo->direction));
	}
	else if (currentAnimationDuration >= PUSH_DURATION)
	{
		pengo->Sprite = ResourceManager::GetTexture("pengo" + stringDirection(pengo->direction));
		pengo->state = PengoState::STAND;
		pengo->ready = true;
	}
}
