#pragma once

#include "../Animator.h"
#include "../Model/Block.h"
#include "../Model/GameObject.h"
#include "ResourceManager.h"

/// <summary>
/// View Class for blocks
/// </summary>
class BlockAnimator : public Animator<GameObject> {
  public:
    Block *block = nullptr;
    Texture2D sprite;
    const float BREAKING_DURATION = 0.0f;
    const float FLASHING_DURATION = 0.0f;
    void (BlockAnimator::*currentAnimation)() = nullptr;

    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="block">pointer to the block for which this is the view object and
    /// that will be observed by this object</param>
    /// <param name="flashingDuration">duration of the flashing animation which appears
    /// after an enemy was killed if this block contains an enemy</param>
    /// <param name="breakingDuration">duration of the breaking animation</param>
    /// <param name="sprite">sprite to be shown for this block</param>
    BlockAnimator(Block *block, float flashingDuration, float breakingDuration, Texture2D sprite);
    
    /// <summary>
    /// Destructor
    /// </summary>
    ~BlockAnimator();

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
    /// Method which realizes the iceblock destruction animation by switching
    /// the sprites accordingly (gets bound to the currentAnimation-pointer)
    /// </summary>
    void destroyIceblock();
    
    /// <summary>
    /// Method which realizes the iceblock flashing animation by switchting 
    /// the sprites accordingly (gets bound to the currentAnimation-pointer)
    /// </summary>
    void flash();
};