#pragma once

#include "Block.h"

/// <summary>
/// Class to manage and update the score
/// </summary>
class Score {
  public:
    int score = 0;

    /// <summary>
    /// Updates the score according to the level completion time
    /// </summary>
    /// <param name="levelDuration">time the player needed to finish the level</param>
    void addLevelCompletion(double levelDuration);

    /// <summary>
    /// Updates the score if diamonds are aligned and at least one of them
    /// is touching the wall
    /// </summary>
    void addDiamondsTouchingWall();

    /// <summary>
    /// Updates the score if diamonds are aligned and none of them is touching
    /// the wall
    /// </summary>
    void addDiamondsNotTouchingWall();

    /// <summary>
    /// Updates the score if the player kills a stunned enemy by walking over it
    /// </summary>
    void addWalkedOverStunnedEnemy();

    /// <summary>
    /// Updates the score if the player kills an enemy with a pushed block
    /// The gained points vary depending on the amount of enemies killed with
    /// one push
    /// </summary>
    /// <param name="killedWithOneMove">amount of enemies killed with one push</param>
    void addCrushedEnemy(int killedWithOneMove);
    /// <summary>
    /// Updates the score if the player destroys a block
    /// </summary>
    /// <param name="block">pointer to the destroyed block</param>
    void addDestroyBlock(Block *block);
};
