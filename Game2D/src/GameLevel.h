#pragma once
#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include <vector>
#include <array>

#include <GL/glew.h>

#include "Constants.h"
#include "GameObject.h"
#include "Player.h"
#include "Block.h"
#include "ResourceManager.h"
#include "Wall.h"
#include "Enemy.h"
#include "GameInformation.h"


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
    Player Pengo;
    std::vector<Enemy*> Enemies;
    std::vector<Enemy*> frozenEnemies;
    std::vector<GameObject> Walls;
    Wall LeftWall;
    Wall RightWall;
    Wall TopWall;
    Wall BottomWall;
    std::vector<Block> Bricks;
    //GameObject d;
    GameInformation P1;
    GameInformation Score;
    bool diamondBlocksAligned = false;
    // constructor
    GameLevel();
    ~GameLevel();
    // loads level from file
    void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
    // render level
    // void Draw(SpriteRenderer& renderer);
    // check if the level is completed (all non-solid tiles are destroyed)
    bool IsCompleted();
private:
    // initialize level from tile data
    void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};

#endif