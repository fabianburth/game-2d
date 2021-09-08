//
// Created by burth on 07.09.2021.
//
#include "../Game2D/src/Model/GameLevel.h"


#include "gtest/gtest.h"

struct TestGameLevel: public GameLevel {
    using GameLevel::blockTouchesWall;

    using GameLevel::checkWallCollision;
    using GameLevel::checkWallCollisionPrecise;

    using GameLevel::checkBlockCollision;

    using GameLevel::checkCollisions;
    using GameLevel::checkCollisionPrecise;
};

TEST(GameLevel, BlockTouchesWall){
    TestGameLevel testGameLevel = TestGameLevel();

    Block testBlock0 = Block({0, 0}, false, nullptr, BlockState::SOLID);
    Block testBlock1 = Block({Constants::WIDTH_UNIT, Constants::HEIGHT_UNIT}, false, nullptr, BlockState::SOLID) ;
    Block testBlock2 = Block({Constants::WIDTH_UNIT*12, Constants::HEIGHT_UNIT*14}, false, nullptr, BlockState::SOLID);
    Block testBlock3 = Block({Constants::WIDTH_UNIT, Constants::HEIGHT_UNIT*12}, false, nullptr, BlockState::SOLID);


    EXPECT_EQ(true, testGameLevel.blockTouchesWall(testBlock0));
    EXPECT_EQ(false, testGameLevel.blockTouchesWall(testBlock1));
    EXPECT_EQ(true, testGameLevel.blockTouchesWall(testBlock2));
    EXPECT_EQ(false, testGameLevel.blockTouchesWall(testBlock3));
}

TEST(GameLevel, CheckWallCollision){
    TestGameLevel testGameLevel = TestGameLevel();

    GameObject testObject0 = GameObject({0, 0});
    GameObject testObject1 = GameObject({Constants::WIDTH_UNIT, Constants::HEIGHT_UNIT}) ;
    GameObject testObject2 = GameObject({Constants::WIDTH_UNIT*12, Constants::HEIGHT_UNIT*14});
    GameObject testObject3 = GameObject({Constants::WIDTH_UNIT, Constants::HEIGHT_UNIT*12});
    GameObject testObject4 = GameObject({Constants::WIDTH_UNIT * 11, 0});
    GameObject testObject5 = GameObject({Constants::WIDTH_UNIT * 11.5f , 0 });

    EXPECT_EQ(false, testGameLevel.checkWallCollision(testObject0, Direction::RIGHT));
    EXPECT_EQ(false, testGameLevel.checkWallCollision(testObject0, Direction::UP));
    EXPECT_EQ(true, testGameLevel.checkWallCollision(testObject0, Direction::LEFT));
    EXPECT_EQ(true, testGameLevel.checkWallCollision(testObject0, Direction::DOWN));

    EXPECT_EQ(false, testGameLevel.checkWallCollision(testObject1, Direction::RIGHT));
    EXPECT_EQ(false, testGameLevel.checkWallCollision(testObject1, Direction::UP));
    EXPECT_EQ(false, testGameLevel.checkWallCollision(testObject1, Direction::LEFT));
    EXPECT_EQ(false, testGameLevel.checkWallCollision(testObject1, Direction::DOWN));

    EXPECT_EQ(false, testGameLevel.checkWallCollisionPrecise(testObject0, Direction::RIGHT));
    EXPECT_EQ(false, testGameLevel.checkWallCollisionPrecise(testObject0, Direction::UP));
    EXPECT_EQ(true, testGameLevel.checkWallCollisionPrecise(testObject0, Direction::LEFT));
    EXPECT_EQ(true, testGameLevel.checkWallCollisionPrecise(testObject0, Direction::DOWN));

    EXPECT_EQ(false, testGameLevel.checkWallCollisionPrecise(testObject1, Direction::RIGHT));
    EXPECT_EQ(false, testGameLevel.checkWallCollisionPrecise(testObject1, Direction::UP));
    EXPECT_EQ(false, testGameLevel.checkWallCollisionPrecise(testObject1, Direction::LEFT));
    EXPECT_EQ(false, testGameLevel.checkWallCollisionPrecise(testObject1, Direction::DOWN));

    // This shows the relevant difference between the two methods
    EXPECT_EQ(true, testGameLevel.checkWallCollision(testObject5, Direction::RIGHT));
    EXPECT_EQ(false, testGameLevel.checkWallCollisionPrecise(testObject5, Direction::RIGHT));
}

TEST(GameLevel, CheckBlockCollision){
    TestGameLevel testGameLevel = TestGameLevel();

    // This object is in the bottom left corner
    GameObject testObject0 = GameObject({0,0});
    // This object is one unit to the right of testObject0 and at the same height
    GameObject testObject1 = GameObject({Constants::WIDTH_UNIT, 0});
    // This object is two units to the right of testObject0 and at the same height
    GameObject testObject2 = GameObject({Constants::WIDTH_UNIT * 2, 0});

    EXPECT_EQ(true, testGameLevel.checkBlockCollision(testObject0, testObject1, Direction::RIGHT));
    EXPECT_EQ(false, testGameLevel.checkBlockCollision(testObject0, testObject2, Direction::RIGHT));

    EXPECT_EQ(true, testGameLevel.checkBlockCollision(testObject1, testObject0, Direction::LEFT));
    EXPECT_EQ(false, testGameLevel.checkBlockCollision(testObject2, testObject0, Direction::LEFT));


    // This object is in the bottom left corner
    GameObject testObject3 = GameObject({0,0});
    // This object is one unit above testObject3
    GameObject testObject4 = GameObject({0, Constants::HEIGHT_UNIT});
    // This object is two units above testObject3
    GameObject testObject5 = GameObject({0, Constants::HEIGHT_UNIT * 2});

    EXPECT_EQ(true, testGameLevel.checkBlockCollision(testObject3, testObject4, Direction::UP));
    EXPECT_EQ(false, testGameLevel.checkBlockCollision(testObject3, testObject5, Direction::UP));

    EXPECT_EQ(true, testGameLevel.checkBlockCollision(testObject4, testObject3, Direction::DOWN));
    EXPECT_EQ(false, testGameLevel.checkBlockCollision(testObject5, testObject3, Direction::DOWN));
}
