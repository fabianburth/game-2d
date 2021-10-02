#include "BlockAnimator.h"

#include "SoundManager.h"

BlockAnimator::BlockAnimator(Block *block, float flashingDuration, float breakingDuration, Texture2D sprite) :
    sprite{sprite}, BREAKING_DURATION{breakingDuration}, FLASHING_DURATION{flashingDuration} {
    this->block = block;
    this->block->registerObserver(this);
}

BlockAnimator::~BlockAnimator() {}

void BlockAnimator::update(GameObject *s) {
    switch (block->state) {
        case (BlockState::BREAKING):
            currentAnimationDuration = 0;
            currentAnimation = &BlockAnimator::destroyIceblock;
            break;
        case (BlockState::FLASHING):
            currentAnimationDuration = 0;
            currentAnimation = &BlockAnimator::flash;
            break;
        case (BlockState::BROKEN):
            currentAnimationDuration = 0;
            currentAnimation = nullptr;
            break;
        default:
            break;
    }
}

void BlockAnimator::animate(float dt) {
    if (currentAnimation != nullptr) {
        (*this.*currentAnimation)();
        currentAnimationDuration += dt;
    }
}

void BlockAnimator::destroyIceblock() {
    if (currentAnimationDuration == 0) {
        this->sprite = ResourceManager::getTexture("iceblockBreaking0");
    } else if (currentAnimationDuration >= (1.0f / 4.0f) * BREAKING_DURATION &&
               currentAnimationDuration < (2.0f / 4.0f) * BREAKING_DURATION) {
        this->sprite = ResourceManager::getTexture("iceblockBreaking1");
    } else if (currentAnimationDuration >= (2.0f / 4.0f) * BREAKING_DURATION &&
               currentAnimationDuration < (3.0f / 4.0f) * BREAKING_DURATION) {
        this->sprite = ResourceManager::getTexture("iceblockBreaking2");
    } else if (currentAnimationDuration >= (3.0f / 4.0f) * BREAKING_DURATION &&
               currentAnimationDuration < BREAKING_DURATION) {
        this->sprite = ResourceManager::getTexture("iceblockBreaking3");
    } else if (currentAnimationDuration >= BREAKING_DURATION) {
        currentAnimationDuration = 0.0f;
        currentAnimation = nullptr;
    }
}

void BlockAnimator::flash() {
    if (currentAnimationDuration == 0) {
        this->sprite = ResourceManager::getTexture("iceblockGreen");
    } else if (currentAnimationDuration >= (1.0f / 5.0f) * FLASHING_DURATION &&
               currentAnimationDuration < (2.0f / 5.0f) * FLASHING_DURATION) {
        this->sprite = ResourceManager::getTexture("iceblock");
    } else if (currentAnimationDuration >= (2.0f / 5.0f) * FLASHING_DURATION &&
               currentAnimationDuration < (3.0f / 5.0f) * FLASHING_DURATION) {
        this->sprite = ResourceManager::getTexture("iceblockGreen");
    } else if (currentAnimationDuration >= (3.0f / 5.0f) * FLASHING_DURATION &&
               currentAnimationDuration < (4.0f / 5.0f) * FLASHING_DURATION) {
        this->sprite = ResourceManager::getTexture("iceblock");
    } else if (currentAnimationDuration >= (4.0f / 5.0f) * FLASHING_DURATION &&
               currentAnimationDuration < FLASHING_DURATION) {
        this->sprite = ResourceManager::getTexture("iceblockGreen");
    } else if (currentAnimationDuration >= FLASHING_DURATION) {
        this->sprite = ResourceManager::getTexture("iceblock");
        currentAnimationDuration = 0.0f;
        currentAnimation = nullptr;
    }
}
