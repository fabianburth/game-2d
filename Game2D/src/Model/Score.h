//
// Created by burth on 27.08.2021.
//
#pragma once

#include "Block.h"


class Score {
  public:
    int score = 0;

    void addLevelCompletion(double levelDuration);
    void addDiamondsTouchingWall();
    void addDiamondsNotTouchingWall();
    void addWalkedOverStunnedEnemy();
    void addCrushedEnemy(int killedWithOneMove);
    void addDestroyBlock(Block *block);
};
