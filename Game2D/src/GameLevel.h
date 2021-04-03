#pragma once
#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include <vector>
#include <array>

#include <GL/glew.h>

#include "gameobject.h"
#include "spriterenderer.h"
#include "resourcemanager.h"


/// GameLevel holds all Tiles as part of a Breakout level and 
/// hosts functionality to Load/render levels from the harddisk.
/// 
/// In a level definition file, each number represents a type of block
/// 0: no block, empty space
/// 1: a destroyable ice block
/// 2: an undestroyable diamond block
/// 3: a sno-bee
/// 4: pengo
class GameLevel
{
public:
    // level state
    std::vector<GameObject> Walls;
    std::vector<GameObject> Bricks;
    // constructor
    GameLevel() { }
    // loads level from file
    void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
    // render level
    void Draw(SpriteRenderer& renderer);
    // check if the level is completed (all non-solid tiles are destroyed)
    bool IsCompleted();
private:
    // initialize level from tile data
    void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};

#endif