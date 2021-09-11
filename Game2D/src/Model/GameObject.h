#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../Constants.h"
//#include <GL/glew.h>
#include <memory>
#include <vector>
#include <array>
#include <string>

//#include "../View/Texture.h"
#include "../Subject.h"

enum class Direction {
    RIGHT,
    LEFT,
    UP,
    DOWN,
    NONE
};

static auto stringDirection(Direction direction) -> std::string {
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

static auto oppositeDirection(Direction direction) -> Direction {
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


/**
 * Container object for holding all state relevant for a single
 * game object entity. Each object in the game likely needs the
 * minimal of state as described within GameObject.
 */
class GameObject : public Subject<GameObject> {
public:
    // object state
    std::array<float, 2> position;
    std::array<float, 4> size;

    GameObject();

    GameObject(std::array<float, 2> pos, std::array<float, 4> size = {1.0f, 1.0f, 0.0f, 0.0f});

    void registerObserver(Observer<GameObject> *o) override;
    void removeObserver(Observer<GameObject> *o) override;
    void notifyObservers() override;

private:
    std::vector<Observer<GameObject> *> observers;
};

#endif