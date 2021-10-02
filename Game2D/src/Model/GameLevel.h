#pragma once
#include <array>
#include <ctime>
#include <memory>
#include <vector>

#include "../Constants.h"
#include "Block.h"
#include "GameObject.h"
#include "Player.h"
#include "../util.h"
#include "Enemy.h"
#include "Score.h"
#include "Wall.h"


class GameLevel : public Subject<GameLevel> {
  public:
    Player Pengo;
    std::vector<std::shared_ptr<Enemy>> Enemies;
    std::vector<std::shared_ptr<Enemy>> frozenEnemies;
    std::vector<GameObject> Walls;
    Wall LeftWall;
    Wall RightWall;
    Wall TopWall;
    Wall BottomWall;
    std::vector<Block> Blocks;

    // Is set to the primary event in specific situations
    Events event;
    // Keeps track of the players score and provides useful methods
    Score score;

    // Clock to track how long it takes the player to finish the level (relevant for score)
    std::clock_t startClockLevel = 0;

    // Clock to track how much time has passed since the last enemy was killed (relevant for enemy state)
    std::clock_t startClockEnemyKill = 0;

    // Is set to true when 3 diamond blocks get aligned
    bool diamondBlocksAligned = false;


    GameLevel() = default;
    ~GameLevel() = default;

    /// <summary>
    /// Method inherited from the Subject template class to register 
    /// objects as observer to be informed about updates in GameLevels state
    /// </summary>
    /// <param name="o">pointer to the object that shall be registered as
    /// observer</param>
    void registerObserver(Observer<GameLevel> *o) override;

    /// <summary>
    /// Method inherited from the Subject template class to remove
    /// objects as observer that should not be informed about
    /// updates in GameLevels state anymore
    /// </summary>
    /// <param name="o">pointer to the object that shall be
    /// removed as registered observer</param>
    void removeObserver(Observer<GameLevel> *o) override;

    /// <summary>
    /// Method inherited from Subject template class to inform
    /// all objects registered as observer about updates
    /// in GameLevels state
    /// </summary>
    void notifyObservers() override;

    /// <summary>
    /// Sets the currently relevant event and informs all obversers
    /// about the change
    /// </summary>
    /// <param name="e">event</param>
    void setEvent(Events e);
    
    /// <summary>
    /// Loads Level from textfile
    /// </summary>
    /// <param name="file">path to the textfile</param>
    void Load(const char *file);
    
    /// <summary>
    /// Check if the level is completed (all non-solid tiles are destroyed)
    /// </summary>
    /// <returns>true, if it is completed, false otherwise</returns>
    bool IsCompleted();

    /// <summary>
    /// Method which is called every game loop iteration which does some checks
    /// and updates the game state under certain conditions
    /// </summary>
    /// <param name="dt">time passed since the last game loop iteration</param>
    void updateGameState(float dt);


    //! Following methods are moved from the Controller (Game) to this Model (GameLevel) to abide with MVC

    /// <summary>
    /// Processes an attack of the Player (=Pressing LeftCtrl) and hence determines whether a block is pushed or
    /// destroyed or whether a wall will wobble
    /// </summary>
    void processPengoAttack();

    /// <summary>
    /// Processes movement of the Player (=Pressing WASD) and hence determines where Pengo will go
    /// </summary>
    /// <param name="d">movement direction</param>
    void processPengoMovement(Direction d);

    /// <summary>
    /// Sets the states of blocks and enemies to an level start state
    /// (Among other reasons, this is functionality is encapsulated in a separate method and is not part of the init
    /// method, because this should be done AFTER the view is initialized so it gets informed about change of states)
    /// </summary>
    void initStates();

  protected:
    std::vector<Observer<GameLevel> *> observers;

    /// <summary>
    /// Initialize level from tile data
    /// </summary>
    /// <param name="tileData">level data from txt-file in a vector</param>
    /// <returns></returns>
    void init(std::vector<std::vector<unsigned int>> tileData);

    //! Following methods are moved from the Controller (Game) to this Model (GameLevel) to abide with MVC

    /// <summary>
    /// Auxiliary method for checkCollisions - checks whether GameObject one collides with GameObject two if it is moved
    /// one unit in the given direction
    /// </summary>
    /// <param name="one">GameObject to be moved</param>
    /// <param name="two">GameObject with which collision will be checked</param>
    /// <param name="d">Direction to which it would be moved</param>
    /// <returns>true, if the blocks would collide, false otherwise</returns>
    static bool checkBlockCollision(GameObject &one, GameObject &two, Direction d);

    /// <summary>
    /// Auxiliary method for checkCollisions - checks whether GameObject will be colliding with the wall when moved one
    /// unit in the given Direction
    /// </summary>
    /// <param name="one">GameObject to be moved</param>
    /// <param name="d">Direction to which it would be moved</param>
    /// <returns>true, if it would collide with the wall, false otherwise</returns>
    static bool checkWallCollision(GameObject &one, Direction d);

    /// <summary>
    /// Auxiliary method, checks whether the given gameObject is touching the wall at the given side (used to check every
    /// game loop iteration, whether enemies are touching the wall and need to be stunned, in case the wall is wobbly -
    /// thus and offset of 1 WIDTH_UNIT as in checkWallCollision would not make sense and lead to enemies being stunned
    /// too early)
    /// </summary>
    /// <param name="one">GameObject to check the collision for</param>
    /// <param name="d">Direction in which collision has to be checked</param>
    /// <returns>true, if it is touching the wall, false otherwise</returns>
    static bool checkWallCollisionPrecise(GameObject &one, Direction d);

    /// <summary>
    /// Auxiliary method which returns a vector containing all directions which are possible for the enemy to move to
    /// 1) In case the enemy is in state wandering, the vector is ordered like:
    ///    [current direction, not current and not opposite, not current and not opposite, opposite direction]
    ///    and then the not possible directions (because there is a wall or a block) are removed from the array
    /// 2) In case the enemy is in state chasing, the vector is ordered like:
    ///    [direction with the greatest distance to pengo, not greatest distance to pengo and not opposite, not greatest
    /// distance to pengo and not opposite, opposite direction] and then the not possible directions (because there is a
    /// wall or an unbreakable block) are removed from the array
    /// </summary>
    /// <param name="enemy">enemy for which the directions array shall get generated</param>
    /// <returns>vector containing the possible directions</returns>
    std::vector<Direction> getInitialDirections(Enemy &enemy);

    /// <summary>
    /// Auxiliary method which determines (an index of a) direction based on the probability vector
    /// </summary>
    /// <param name="chances">probability vector for this enemy</param>
    /// <returns>index of the direction in a direction vector</returns>
    static int getDirectionIndex(const std::vector<int> &chances);

    /// <summary>
    /// Auxiliary method which checks whether 3 diamond blocks got aligned and updates the score if so
    /// </summary>
    void checkThreeDiamonds();

    /// <summary>
    /// Auxiliary method which checks whether a block touches a wall
    /// </summary>
    /// <param name="b">block to check whether it touches the wall</param>
    /// <returns>true, if it touches the wall, false otherwise</returns>
    bool blockTouchesWall(Block &b);

    /// <summary>
    /// Auxiliary method which determines and update the game state concerning bots behavior, movement and their
    /// interaction with the player and the environment
    /// </summary>
    /// <param name="dt">time passed since the last game loop iteration</param>
    void determineBotBehavior(float dt);

    /// <summary>
    /// Auxiliary method which updates the game state concerning block movement and their interaction with the
    /// environment
    /// </summary>
    /// <param name="dt">time passed since the last game loop iteration</param>
    void updateBlockInteractions(float dt);

    /// <summary>
    /// Sets one of the remaining active enemies to type boxer if possible
    /// </summary>
    /// <returns></returns>
    void trySettingBoxer();


    /// <summary>
    /// Checks whether an enemy of type boxer exists at the moment
    /// </summary>
    /// <returns>true, if one exists, false otherwise</returns>
    bool boxerExists();

    /// <summary>
    /// Spawns one of the currently frozen enemies
    /// </summary>
    void spawnEnemy();

    /// <summary>
    /// Checks whether the given gameObject is colliding with another block or a wall when moving one unit to the given
    /// direction
    /// </summary>
    /// <param name="gameObject">GameObject to check the collision for</param>
    /// <param name="d">Direction in which collision has to be checked</param>
    /// <returns>true, if there is a collision, false otherwise</returns>
    bool checkCollisions(GameObject &gameObject, Direction d);

    /// <summary>
    /// Return the Block with which the given GameObject is colliding
    /// </summary>
    /// <param name="gameObject">GameObject to check the collision for</param>
    /// <param name="d">Direction in which collision has to be checked</param>
    /// <returns>pointer to the gameObject with which the given GameObject is colliding or nullptr otherwise</returns>
    Block* getCollisionBlock(GameObject &gameObject, Direction d);

    /// <summary>
    /// Calculates how many units the given GameObject could move until colliding with another block or the wall (step
    /// range)
    /// </summary>
    /// <param name="block">GameObject the step range has to be calculated for</param>
    /// <param name="d">Direction in which the step range has to be checked</param>
    /// <returns>how many units the block can move until it collides with another block
    /// or a wall</returns>
    int calculateStepRange(Block &block, Direction d);

    /// <summary>
    /// Checks whether the given gameObject is colliding with another gameObject
    /// </summary>
    /// <param name="one">GameObject to check the collision</param>
    /// <param name="two">GameObject to check the collision</param>
    /// <returns>true, if the blocks collide false otherwise</returns>
    static bool checkCollisionPrecise(GameObject &one, GameObject &two);


    /// <summary>
    /// Removes the enemy from the vector of active enemies
    /// </summary>
    /// <param name="enemy">pointer to the enemy to be removed</param>
    /// <returns></returns>
    void killEnemy(std::shared_ptr<Enemy> &enemy);
};
