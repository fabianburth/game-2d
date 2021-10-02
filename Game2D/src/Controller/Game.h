#pragma once

#include "../Constants.h"
#include "../Model/GameLevel.h"
#include "../Model/Player.h"
#include "../Model/Wall.h"
#include "../View/SoundModule.h"
#include "../View/SpriteRenderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>

// Represents the current state of the game
enum class GameState { GAME_ACTIVE, GAME_MENU, GAME_WIN };

float constexpr EPSILON = 0.01;

/// <summary>
/// Game holds all game-related state and functionality.
/// Combines all game-related data into a single class for
/// easy access to each of the components and manageability.
/// </summary>
class Game : public Observer<GameLevel> {
  public:
    GameState pengoState;
    SpriteRenderer *renderer = nullptr;
    SoundModule *soundModule = nullptr;
    bool keys[1024];
    unsigned int width, height;
    std::vector<GameLevel> levels;
    unsigned int level = 0;

    /// Constructor
    Game(unsigned int width, unsigned int height);
    /// Destructor
    ~Game();

    /// <summary>
    /// Initialize Game (load all shaders and levels and initialize
    /// View and Sound)
    /// </summary>
    void init();

    /// <summary>
    /// Method called in the Game Loop
    /// Receives user input and calls corresponding model methods
    /// </summary>
    /// <param name="dt">time since the last game loop iteration</param>
    void processInput(float dt);

    /// <summary>
    /// Method called in the Game Loop
    /// Checks whether a level is over or completed and calls specific methods
    /// respectively
    /// Calls Model and View methods to update the view and model
    /// </summary>
    /// <param name="dt">time since the last game loop iteration</param>
    void update(float dt);

    /// <summary>
    /// Method called in the Game Loop
    /// Calls the corresponding View method to display the game
    /// </summary>
    void render();

    /// <summary>
    /// Method inherited from Observer template class
    /// </summary>
    /// <param name="s">pointer to the subject which informed about the update</param>
    void update(GameLevel *s) override;

  private:
    /// <summary>
    /// Manages the begin of the level and also the transition to another level
    /// Initiates the initialization of states and also binds all observers necessary
    /// </summary>
    void initLevel();
    
    /// <summary>
    /// Carries the score of the finished level over to the next level
    /// </summary>
    void carryOverScore();
};
