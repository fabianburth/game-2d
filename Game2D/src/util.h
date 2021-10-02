#pragma once

#include <string>

enum class Direction { RIGHT, LEFT, UP, DOWN, NONE };

auto stringDirection(Direction direction) -> std::string;

auto oppositeDirection(Direction direction) -> Direction;

enum class pengoState { STAND, WALK, PUSH, BREAK };

auto stringState(pengoState state) -> std::string;

enum class Events {
    ENEMY_KILLED,
    ENEMY_SPAWNED,
    PENGO_DIED,
    STUNNED_ENEMY_KILLED,
    ENEMY_STUNNED,
    BREAK_ICE_BLOCK,
    PUSH_BLOCK,
    WOBBLE_WALL,
    SUDDEN_DEATH,
    ENEMY_CRUSHED,
    DIAMONDS_ALIGNED
};
