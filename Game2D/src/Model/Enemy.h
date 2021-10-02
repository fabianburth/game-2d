#pragma once
#include "../util.h"
#include "GameObject.h"

enum class EnemyType { CHASING, WANDERING };

enum class EnemyState { BREAKING, STUNNED, SPAWNING, INITIAL_SPAWNING, NONE };

/// <summary>
/// Class representing Sno-Bees
/// </summary>
class Enemy : public GameObject {
  public:
    unsigned int id;
    Direction direction;
    EnemyState state;
    EnemyType type;
    std::array<float, 2> velocity, positionToMoveTo;
    bool ready;

    static constexpr float BREAKING_BLOCK_DURATION = 0.5f;
    static constexpr float STUNN_DURATION = 3.0f;
    static constexpr float SPAWN_DURATION = 1.5f;
    float breakingBlockFor = 0.0f;
    float stunnedFor = 0.0f;
    float spawningFor = 0.0f;

    /// <summary>
    /// Default Constructor
    /// </summary>
    Enemy();

    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="pos">position of the enemy</param>
    /// <param name="velocity">velocity of the enemy</param>
    /// <param name="direction">direction of the enemy</param>
    /// <param name="state">enemy state </param>
    /// <param name="type">enemy type</param>
    /// <param name="ready">determines whether it will move from the beginning or not
    /// f.e. false for frozen enemies</param>
    Enemy(std::array<float, 2> pos, std::array<float, 2> velocity, Direction direction, EnemyState state,
          EnemyType type, bool ready);

    /// <summary>
    /// Sets the direction of the enemy
    /// </summary>
    /// <param name="direction">enemy direction</param>
    void setDirection(Direction direction);

    /// <summary>
    /// Sets the state of the enemy
    /// </summary>
    /// <param name="state">enemy state</param>
    void setState(EnemyState state);

    /// <summary>
    /// Sets the type of the enemy
    /// </summary>
    /// <param name="type">enemy type</param>
    void setType(EnemyType type);

    /// <summary>
    /// Sets the position the enemy has to move to
    /// </summary>
    void setPositionToMoveTo();

    /// <summary>
    /// Called every Game Loop Iteration and moves the enemy into his
    /// current direction if position is not equal to positionToMoveTo
    /// dependant on deltaTime and velocity
    /// </summary>
    /// <param name="deltaTime">time since the last game loop iteration</param>
    void move(float deltaTime);

    /// <summary>
    /// Auxiliary method which generates a vector containing probabilities for
    /// the possible directions
    /// </summary>
    /// <param name="directions">A vector containing all possible directions
    /// for the enemy to move to, usually the result of the 
    /// GameLevel::getInitialDirections-Method</param>
    /// <returns>A vector containing a probability for each direction in the 
    /// direction vector</returns>
    auto getProbabilityArray(std::vector<Direction> directions) -> std::vector<int>;

  protected:
    static unsigned int nextID;
};