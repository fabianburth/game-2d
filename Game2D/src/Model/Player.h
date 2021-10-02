#pragma once

#include "../util.h"
#include "GameObject.h"

#include <string>
#include <vector>

class Player : public GameObject {
  public:
    Direction direction = Direction::NONE;
    pengoState state = pengoState::STAND;
    std::array<float, 2> velocity, positionToMoveTo;
    bool ready;
    int lives = 1;

    static constexpr float WALKING_DURATION = 0.25f;
    static constexpr float PUSHING_DURATION = 0.5f;
    static constexpr float BREAKING_BLOCK_DURATION = 0.5f;
    float walkingFor = 0.0f;
    float pushingFor = 0.0f;
    float breakingBlockFor = 0.0f;

    /// <summary>
    /// Default Constructor
    /// </summary>
    Player();

    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="pos">position of the player</param>
    /// <param name="velocity">velocity of the player</param>
    Player(std::array<float, 2> pos, std::array<float, 2> velocity);

    /// <summary>
    /// Sets Players direction
    /// </summary>
    /// <param name="direction">direction to be set</param>
    void setDirection(Direction direction);

    /// <summary>
    /// Sets Players state
    /// </summary>
    /// <param name="state">state to be set</param>
    void setState(pengoState state);

    /// <summary>
    /// Sets position to move to
    /// </summary>
    void setPositionToMoveTo();

    /// <summary>
    /// Called every Game Loop Iteration and moves the block into his
    /// current direction if position is not equal to positionToMoveTo
    /// dependant on deltaTime and velocity
    /// </summary>
    /// <param name="deltaTime">time since the last game loop iteration</param>
    void move(float deltaTime);
};