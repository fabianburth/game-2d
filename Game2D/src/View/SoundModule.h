#pragma once
#include "../Model/GameLevel.h"
#include "../Observer.h"
#include "../util.h"
#include "SoundManager.h"
class SoundModule : public Observer<GameLevel> {
  public:

    /// <summary>
    /// Method inherited from Animator template class
    /// Triggers sounds for specific events using the sound manager
    /// </summary>
    /// <param name="s">pointer to the subject which informed about the update</param>
    void update(GameLevel *gameLevel) override;

    /// <summary>
    /// Constructor
    /// </summary>
    SoundModule();

  private:
    SoundManager *soundManager;

    /// <summary>
    /// Loads all necessary audio data
    /// </summary>
    void initGameSounds();
};