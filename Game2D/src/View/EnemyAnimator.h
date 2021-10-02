#pragma once

#include "../Animator.h"
#include "../Model/Enemy.h"
#include "ResourceManager.h"

#include <string>

class EnemyAnimator : public Animator<GameObject> {
  public:
    std::shared_ptr<Enemy> enemy;
    Texture2D sprite;
    std::string spriteType;
    const float WALK_ANIMATION_DURATION;
    const float STUNNED_ANIMATION_DURATION;
    const float SPAWNING_ANIMATION_DURATION;
    void (EnemyAnimator::*currentAnimation)() = nullptr;

    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="enemy">pointer to the enemy for which this is the view object and
    /// that will be observed by this object</param>
    /// <param name="walkAnimationDuration">duration of the walk animation</param>
    /// <param name="stunnedAnimationDuration">duration of the stunn animation</param>
    /// <param name="spawningAnimationDuration">duration of the spawning animation</param>
    EnemyAnimator(std::shared_ptr<Enemy> enemy, float walkAnimationDuration, float stunnedAnimationDuration,
                  float spawningAnimationDuration);

    /// Destructor
    ~EnemyAnimator();

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
    /// Method which realizes the walk animation by switching
    /// the sprites accordingly (gets bound to the currentAnimation-pointer)
    /// </summary>
    void walk();

    /// <summary>
    /// Method which realizes the iceblock destroying animation by switching
    /// the sprites accordingly (gets bound to the currentAnimation-pointer)
    /// </summary>
    void breakBlock();

    /// <summary>
    /// Method which realizes the stunned animation by switching
    /// the sprites accordingly (gets bound to the currentAnimation-pointer)
    /// </summary>
    void stunned();

    /// <summary>
    /// Method which realizes the spawning animation by switching
    /// the sprites accordingly (gets bound to the currentAnimation-pointer)
    /// </summary>
    void spawning();

    /// <summary>
    /// Method which realizes the spawning from iceblock by switching
    /// the sprites accordingly (gets bound to the currentAnimation-pointer)
    /// </summary>
    void spawningFromBlock();
};