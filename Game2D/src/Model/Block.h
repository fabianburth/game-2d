#pragma once

#include "../util.h"
#include "Enemy.h"
#include "GameObject.h"

#include <string>
#include <vector>

enum class BlockState { SOLID, BREAKING, BROKEN, SPAWNING, FLASHING };

class Block : public GameObject {
  public:
    // Movement speed when block is pushed
    inline static const std::array<float, 2> VELOCITY = {Constants::WIDTH_UNIT * 12, Constants::HEIGHT_UNIT * 12};
    // Current state of the block
    BlockState state = BlockState::SOLID;
    /** 
     Target position of the block when it is pushed (= the block will move
     until the position equals the positionToMoveTo
     */
    std::array<float, 2> positionToMoveTo;
    /**
     Determines whether the block is an iceblock (=breakable) or a diamond
     block (=unbreakable)
     */
    bool isUnbreakable;
    /**
     Pointer to the enemy that is contained within the block
     If it is a normal iceblock, this will be nullptr, if it is a block
     an enemy can spawn from, it is a pointer to that enemy
     */
    std::shared_ptr<Enemy> containedEnemy;
    // Current movement direction of the block
    Direction direction;
    /**
     If the block is pushed, this counter is increased by one for each enemy
     it hits on the way (relevant for score)
     Resetted to 0 once the block reach its target location (positionToMoveTo),
     so once it reaches another block or a wall
     */
    int killedWithOneMove = 0;

    static constexpr float BREAKING_DURATION = 0.5f;
    static constexpr float FLASHING_DURATION = 3.0f;
    float breakingFor = 0.0f;
    float flashingFor = 0.0f;

    /// <summary>
    /// Default Constructor
    /// </summary>
    Block();

    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="pos">position of the block</param>
    /// <param name="isUnbreakable">determines whether the block is an iceblock
    /// (=breakable) or a diamond block (=unbreakable)</param>
    /// <param name="containedEnemy">pointer to the enemy that is contained within the block</param>
    /// <param name="state">state of the block</param>
    Block(std::array<float, 2> pos, bool isUnbreakable, std::shared_ptr<Enemy> containedEnemy, BlockState state);

    /// <summary>
    /// Sets the state of the block and notifies observers
    /// </summary>
    /// <param name="state">state of the block</param>
    void setState(BlockState state);

    /// <summary>
    /// Sets the position the block has to move to
    /// </summary>
    /// <param name="direction">direction in which it has to move</param>
    void setPositionToMoveTo(Direction direction);

    /// <summary>
    /// Sets the position the block has to move to when it is pushed
    /// </summary>
    /// <param name="direction">direction in which the block is pushed</param>
    /// <param name="stepRange">how many units it can move</param>
    void push(Direction direction, int stepRange);

    /// <summary>
    /// Called every Game Loop Iteration and moves the block into his 
    /// current direction if position is not equal to positionToMoveTo
    /// dependant on deltaTime and velocity
    /// </summary>
    /// <param name="deltaTime">time since the last game loop iteration</param>
    void move(float deltaTime);
};