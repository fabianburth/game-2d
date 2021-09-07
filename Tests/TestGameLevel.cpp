//
// Created by burth on 07.09.2021.
//
#include "../Game2D/src/Model/GameLevel.h"
#include "../Game2D/src/Model/Block.h"
#include "../Game2D/src/Model/Enemy.h"
#include "../Game2D/src/Model/Player.h"
#include "../Game2D/src/Model/Player.h"

#include "gtest/gtest.h"

class TestGameLevel: public GameLevel {
public:
    bool blockTouchesWall(Block &b);
};

TEST(GameLevel, BlockTouchesWall){
    TestGameLevel testGameLevel = TestGameLevel();
    Block block = Block({0,0}, false, nullptr, BlockState::SOLID);
    EXPECT_EQ(true, testGameLevel.blockTouchesWall(block));
}