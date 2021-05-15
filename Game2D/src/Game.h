#pragma once

#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GameLevel.h"
#include "Player.h"

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
    bool         Keys[1024];
    unsigned int Width, Height;
    std::vector<GameLevel>  Levels;
    unsigned int            Level;
    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render();
    bool checkCollisions(Direction d);
    bool doCollision(Direction d);

private:
    bool checkCollisionRight(GameObject& one, GameObject& two);
    bool checkCollisionLeft(GameObject& one, GameObject& two);
    bool checkCollisionUp(GameObject& one, GameObject& two);
    bool checkCollisionDown(GameObject& one, GameObject& two);
};

#endif