#pragma once

#include "../Constants.h"
#include "../Model/GameLevel.h"
#include "../Model/GameObject.h"
#include "../View/BlockAnimator.h"
#include "../View/EnemyAnimator.h"
#include "../View/PengoAnimator.h"
#include "../View/SoundManager.h"
#include "../View/WallAnimator.h"
#include "GameInformation.h"
#include "Shader.h"
#include "Texture.h"

#include <GL/glew.h>
#include <array>

/// <summary>
/// Central View Class which is responsible for rendering whole Game Levels
/// </summary>
class SpriteRenderer : public Observer<GameLevel> {
  public:
    // View Objects
    PengoAnimator *pengoAnimator;
    // BlockAnimator* blockAnimator;
    WallAnimator *leftWallAnimator;
    WallAnimator *rightWallAnimator;
    WallAnimator *bottomWallAnimator;
    WallAnimator *topWallAnimator;

    std::vector<BlockAnimator *> blockAnimators;
    std::vector<EnemyAnimator *> enemyAnimators;

    GameInformation P1;
    GameInformation Score;

    SpriteRenderer() = default;

    /// <summary>
    /// Constructor (inits shaders/shapes)
    /// </summary>
    /// <param name="shader">a shader</param>
    SpriteRenderer(Shader &shader);

    /// Destructor
    ~SpriteRenderer();

    /// <summary>
    /// Renders a defined quad textured with given sprite
    /// </summary>
    /// <param name="texture">texture to be rendered</param>
    /// <param name="position">position where the texture should be rendered</param>
    /// <param name="size">size of the texture</param>
    /// <param name="color">color of the texture</param>
    void drawSprite(Texture2D &texture, std::array<float, 2> position, std::array<float, 4> size,
                    std::array<float, 3> color = {1.0f, 1.0f, 1.0f});

    /// <summary>
    /// Renders a whole game level
    /// </summary>
    /// <param name="gameLevel">a game level</param>
    void drawLevel(GameLevel &gameLevel);

    /// <summary>
    /// Updates all view objects by calling the respective animate methods
    /// </summary>
    /// <param name="dt">time since the last game loop iteration</param>
    void updateView(float dt);

    /// <summary>
    /// Initializes all view objects of a game level
    /// </summary>
    /// <param name="gameLevel">a game level</param>
    void initLevelView(GameLevel *gameLevel);

    /// <summary>
    /// Method inherited from Animator template class
    /// </summary>
    /// <param name="s">pointer to the subject which informed about the update</param>
    void update(GameLevel *gameLevel) override;

  private:
    // Render state
    Shader shader;
    unsigned int quadVAO;

    /// <summary>
    /// Initializes and configures the quad's buffer and vertex attributes
    /// Thus, it creates the a quad at the bottom left corner
    /// </summary>
    void initRenderData();

    /// <summary>
    /// Renders a display elements
    /// </summary>
    /// <param name="gameInformation"></param>
    void DrawDisplayElement(GameInformation &gameInformation);

    /// <summary>
    /// Initializes all Display Information
    /// </summary>
    void initDisplayInformation();

    /// <summary>
    /// Loads all necessary textures
    /// </summary>
    void loadSprites();

    /// <summary>
    /// Removes animator of killed enemy
    /// </summary>
    /// <param name="enemy">pointer to the enemy</param>
    void removeAnimatorOfKilledEnemy(std::shared_ptr<Enemy> &enemy);

    /// <summary>
    /// Creates animator for spawned enemy
    /// </summary>
    /// <param name="enemy">pointer to the enemy</param>
    void createAnimatorForSpawnedEnemy(std::shared_ptr<Enemy> &enemy);
};
