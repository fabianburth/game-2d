//
// Created by burth on 14.09.2021.
//

#ifndef GAME2D_UTIL_H
#define GAME2D_UTIL_H

#include <string>

enum class Direction {
    RIGHT,
    LEFT,
    UP,
    DOWN,
    NONE
};

auto stringDirection(Direction direction) -> std::string;

auto oppositeDirection(Direction direction) -> Direction;

enum class PengoState
        {
    STAND,
    WALK,
    PUSH,
    BREAK
        };

auto stringState(PengoState state) -> std::string;

#endif //GAME2D_UTIL_H
