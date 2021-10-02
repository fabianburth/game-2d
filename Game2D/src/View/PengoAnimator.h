#pragma once

#include "../Animator.h"
#include "../Model/Player.h"
#include "ResourceManager.h"


/// <summary>
/// View class for Player
/// </summary>
class PengoAnimator : public Animator<GameObject> {
  public:
    Player *pengo;
    Texture2D sprite;
    bool toggleSprite;
    const float PUSH_DURATION;
    const float WALK_ANIMATION_DURATION;
    void (PengoAnimator::*currentAnimation)();

    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="pengo">pointer to the block for which this is the view object and
    /// that will be observed by this object</param>
    /// <param name="pushDuration">duration of the push animation</param>
    /// <param name="walkAnimationDuration">duration of the walk animation</param>
    /// <param name="sprite">sprite to be shown</param>
    PengoAnimator(Player *pengo, float pushDuration, float walkAnimationDuration, Texture2D sprite);

    /// Destructor
    ~PengoAnimator();

    /// <summary>
    /// Method inherited from Animator template class
    /// </summary>
    /// <param name="s">pointer to the subject which informed about the update</param>
    void update(GameObject *s) override;

    /// <summary>
    /// Method which is called every game loop which updates the current sprite
    /// by calling the method to which the currentAnimation pointer currently
    /// points to
    /// </summary>
    /// <param name="dt">time since the last game loop iteration</param>
    void animate(float dt) override;

    /// <summary>
    /// Method which realizes the stand animation by switching
    /// the sprites accordingly (gets bound to the currentAnimation-pointer)
    /// </summary>
    void stand();

    /// <summary>
    /// Method which realizes the walk animation by switching
    /// the sprites accordingly (gets bound to the currentAnimation-pointer)
    /// </summary>
    void walk();

    /// <summary>
    /// Method which realizes the push animation by switching
    /// the sprites accordingly (gets bound to the currentAnimation-pointer)
    /// </summary>
    void pushBlock();

    /// <summary>
    /// Method which realizes the breaking animation by switching
    /// the sprites accordingly (gets bound to the currentAnimation-pointer)
    /// </summary>
    void breakBlock();

    /// <summary>
    /// Method which realizes the breaking animation by switching
    /// the sprites accordingly (gets bound to the currentAnimation-pointer)
    /// </summary>
    void swapSprite();
};