//
// Created by burth on 14.09.2021.
//

#include "util.h"


auto stringDirection(Direction direction) -> std::string {
    switch (direction) {
        case Direction::RIGHT:
            return "Right";
            break;
        case Direction::LEFT:
            return "Left";
            break;
        case Direction::UP:
            return "Up";
            break;
        case Direction::DOWN:
            return "Down";
            break;
        case Direction::NONE:
            return "None";
            break;
        default:
            return "";
            break;
    }
}

auto oppositeDirection(Direction direction) -> Direction {
    switch (direction) {
        case Direction::RIGHT:
            return Direction::LEFT;
            break;
        case Direction::LEFT:
            return Direction::RIGHT;
            break;
        case Direction::UP:
            return Direction::DOWN;
            break;
        case Direction::DOWN:
            return Direction::UP;
            break;
        case Direction::NONE:
        default:
            return Direction::NONE;
            break;
    }
}

auto stringState(PengoState state) -> std::string {
    switch (state) {
        case PengoState::STAND:
            return "Stand";
            break;
        case PengoState::WALK:
            return "Walk";
            break;
        case PengoState::PUSH:
            return "Push";
            break;
        case PengoState::BREAK:
            return "Break";
            break;
        default:
            return "";
            break;
    }
}