//
// Created by burth on 12.09.2021.
//
#include "../Game2D/src/Model/Enemy.h"
#include <memory>


#include "gtest/gtest.h"

struct TestEnemy : public Enemy {
    using Enemy::getProbabilityArray;
};

TEST(Enemy, ProbabilityArray) {
    std::vector<Direction> testDirections0 = {Direction::UP, Direction::RIGHT, Direction::LEFT, Direction::DOWN};
    std::vector<int> expectedProbabilities0 = {90, 94, 98, 100};
    EXPECT_EQ(expectedProbabilities0, testDirections0);
}