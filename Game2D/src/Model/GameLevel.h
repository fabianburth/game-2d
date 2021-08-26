#pragma once
#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include <vector>
#include <array>

#include <GL/glew.h>

#include "../Constants.h"
#include "GameObject.h"
#include "Player.h"
#include "Block.h"
#include "../View/ResourceManager.h"
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
    int score;
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


    //! Following methods are moved from the Controller (Game) to this Model (GameLevel) to abide with MVC
    // Checks whether the given gameObject is colliding with another brick or a wall when moving one unit to the given direction
    // @param gameObject: The GameObject to check the collision for
    // @param direction: The Direction in which collision has to be checked
    // @return true, if there is a collision, false otherwise
    bool checkCollisions(GameObject& gameObject, Direction d);

    // Return the Block with which the given GameObject is colliding
    // @param gameObject: The GameObject to check the collision for
    // @param direction: The Direction in which collision has to be checked
    // @return a pointer to the gameObject with which the given GameObject is colliding or nullptr otherwise
    Block* getCollisionBlock(GameObject& gameObject, Direction d);

    // Calculates how many units the given GameObject could move until colliding with another block or the wall (step range)
    // @param gameObject: The GameObject the step range has to be calculated for
    // @param direction: The Direction in which the step range has to be checked
    int  calculateStepRange(Block& block, Direction d);

    // Checks whether the given gameObject is colliding with a wall
    // @param gameObject: The GameObject to check the collision for
    // @param direction: The Direction in which collision has to be checked
    // @return true, if there is a collision, false otherwise
    bool checkWallCollisionPrecise(GameObject& one, Direction d);

    // Checks whether the given gameObject is colliding with another gameObject
    // @param one: The GameObject to check the collision
    // @param two: The GameObject to check the collision
    bool checkCollisionPrecise(GameObject& one, GameObject& two);

private:
    // initialize level from tile data
    void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);

    //! Following methods are moved from the Controller (Game) to this Model (GameLevel) to abide with MVC
    // Auxiliary method for checkCollisions - checks whether GameObject one collides with GameObject two if it is moved
    // one unit in the given Direction
    // @param one: The GameObject to be moved
    // @param two: The GameObject with which collision will be checked
    // @param d: The Direction to which it would be moved
    bool checkBlockCollision(GameObject& one, GameObject& two, Direction d);

    // Auxiliary method for checkCollisions and doCollisions - checks whether GameObject one collides with the Wall if it is moved on unit
    // in the given Direction
    // @param one: The GameObject to be moved
    // @param d: The Direction to which it would be moved
    bool checkWallCollision(GameObject& one, Direction d);

    // Auxiliary method which returns a vector containing all directions which are possible for the enemy to move to
    // 1) In case the enemy is in state wandering, the vector is ordered like:
    //    [current direction, not current and not opposite, not current and not opposite, opposite direction]
    //    and then the not possible directions (because there is a wall or a block) are removed from the array
    // 2) In case the enemy is in state chasing, the vector is ordered like:
    //    [direction with the greatest distance to pengo, not greatest distance to pengo and not opposite, not greatest distance to pengo and not opposite, opposite direction]
    //    and then the not possible directions (because there is a wall or an unbreakable block) are removed from the array
    // @param enemy: The enemy for which the directions array shall get generated
    // @return: The vector containing the possible directions
    std::vector<Direction> getInitialDirections(Enemy& enemy);

    // Auxiliary method which determines (an index of a) direction based on the probability vector
    // @param chances: A probability vector for this enemy
    // @return: The index of the direction in a direction vector
    int getDirectionIndex(std::vector<int> chances);

    // Auxiliary method which checks whether 3 diamond blocks got aligned
    // @return true, if 3 diamond blocks are aligned, false otherwise
    bool checkThreeDiamonds();

    // Auxiliary method which checks whether a block touches a wall
    // @param b: The block to check whether it touches the wall
    // @return true, if it touches the wall, false otherwise
    bool blockTouchesWall(Block& b);
};

#endif