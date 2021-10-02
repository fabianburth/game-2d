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

auto stringState(pengoState state) -> std::string {
    switch (state) {
        case pengoState::STAND:
            return "Stand";
            break;
        case pengoState::WALK:
            return "Walk";
            break;
        case pengoState::PUSH:
            return "Push";
            break;
        case pengoState::BREAK:
            return "Break";
            break;
        default:
            return "";
            break;
    }
}