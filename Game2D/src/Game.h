#pragma once

#ifndef GAME_H
#define GAME_H

#include "Constants.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <cstdlib>
#include "PengoAnimator.h"
#include "BlockAnimator.h"
#include "WallAnimator.h"
#include "GameLevel.h"
#include "Player.h"
#include "SpriteRenderer.h"
#include "Wall.h"
#include "EnemyAnimator.h"
#include <string>
#include <ctime>

// Represents the current state of the game
enum class GameState 
{
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

const float EPSILON = 0.01;


// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game
{
public:
    // game state
    GameState    PengoState;
    Player* Pengo;
    SpriteRenderer* Renderer;
    PengoAnimator* pengoAnimator;
    BlockAnimator* blockAnimator;
    WallAnimator* wallAnimator;
    std::vector<BlockAnimator*> blockAnimators;
    std::vector<EnemyAnimator*> enemyAnimators;
    bool         Keys[1024];
    unsigned int Width, Height;
    std::vector<GameLevel>  Levels;
    unsigned int            Level;
    unsigned int score = 0;
    std::clock_t startClockLevel;
    std::clock_t startClockEnemyKill;
    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();

private:
    // Checks whether the given gameObject is colliding with another brick or a wall when moving one unit to the given direction
    // @param gameObject: The GameObject to check the collision for
    // @param direction: The Direction in which collision has to be checked
    // @return true, if there is a collision, false otherwise
    bool checkCollisions(GameObject& gameObject, Direction d);

    // Checks whether the given gameObject is colliding with another brick or a wall when moving one unit to the given direction AND 
    // initiates a corresponding action 
    // @param gameObject: The GameObject to check the collision for
    // @param direction: The Direction in which collision has to be checked
    // @return true, if there is a collision, false otherwise
    bool doCollision(GameObject& gameObject, Direction d);

    // Return the Block with which the given GameObject is colliding
    // @param gameObject: The GameObject to check the collision for
    // @param direction: The Direction in which collision has to be checked
    // @return a pointer to the gameObject with which the given GameObject is colliding or nullptr otherwise
    Block* getCollisionBlock(GameObject& gameObject, Direction d);

    // Calculates how many units the given GameObject could move until colliding with another block or the wall (step range)
    // @param gameObject: The GameObject the step range has to be calculated for
    // @param direction: The Direction in which the step range has to be checked
    int  calculateStepRange(Block& block, Direction d);

    // Auxialiary method for checkCollisions and doCollisions - checks whether GameObject one collides with GameObject two if it is moved
    // one unit in the given Direction
    // @param one: The GameObject to be moved
    // @param two: The GameObject with which collision will be checked
    // @param d: The Direction to which it would be moved
    bool checkBlockCollision(GameObject& one, GameObject& two, Direction d);

    // Auxialiary method for checkCollisions and doCollisions - checks whether GameObject one collides with the Wall if it is moved on unit
    // in the given Direction
    // @param one: The GameObject to be moved
    // @param d: The Direction to which it would be moved
    bool checkWallCollision(GameObject& one, Direction d);
    bool checkWallCollisionPrecise(GameObject& one, Direction d);

    bool checkCollisionPrecise(GameObject& one, GameObject& two);

    std::vector<int> getPropabilityArray(Enemy& enemy, std::vector<Direction> directions);
    std::vector<Direction> getInitialDirections(Enemy& enemy);
    int getDirectionIndex(std::vector<int> chances);
    bool isMovementPossible(Enemy& enemy, Direction d);
    void killEnemy(Enemy* enemy);
    void spawnEnemy();
    bool boxerExists();
    void trySettingBoxer();
    void initNextLevel();
    bool checkThreeDiamonds();
    Block* adjacentBlockIsDiamond(Block& b);
    bool blockTouchesWall(Block& b);
};

#endif