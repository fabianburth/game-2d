#pragma once

#include "../Animator.h"
#include "../Model/Wall.h"
#include "ResourceManager.h"

class WallAnimator : public Animator<Wall> {
  public:
    Wall *wall = nullptr;
    Texture2D sprite;
    Texture2D standardSprite;
    Texture2D wobblySprite0;
    Texture2D wobblySprite1;
    const float WOBBLE_DURATION = 0.0f;
    void (WallAnimator::*currentAnimation)() = nullptr;

    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="wall">pointer to a wall</param>
    /// <param name="wobbleDuration">duration of the wobble animation</param>
    WallAnimator(Wall *wall, float wobbleDuration);

    /// Destructor
    ~WallAnimator();

    /// <summary>
    /// Method inherited from Animator template class
    /// </summary>
    /// <param name="s">pointer to the subject which informed about the update</param>
    void update(Wall *s) override;

    /// <summary>
    /// Method which is called every game loop which updates the current sprite
    /// by calling the method to which the currentAnimation pointer currently
    /// points to
    /// </summary>
    /// <param name="dt">time since the last game loop iteration</param>
    void animate(float dt) override;

    /// <summary>
    /// Method which realizes the wobble animation by switchting
    /// the sprites accordingly (gets bound to the currentAnimation-pointer)
    /// </summary>
    void wobble();
};
