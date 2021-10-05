#include "Game.h"

#include "../View/ResourceManager.h"

#include <array>
#include <iostream>

Game::Game(unsigned int width, unsigned int height) :
    pengoState(GameState::GAME_ACTIVE), keys(), width(width), height(height) {}

Game::~Game() {
    delete this->renderer;
}

void Game::init() {
    // load shaders
    ResourceManager::loadShader("../Game2D/res/shaders/sprites.vs", "../Game2D/res/shaders/sprites.fs", "sprite");
    // configure shaders
    ResourceManager::getShader("sprite").use().setInteger("image", 0);
    // set render-specific controls
    Shader shader = ResourceManager::getShader("sprite");
    this->renderer = new SpriteRenderer(shader);
    this->soundModule = new SoundModule();

    // load levels
    GameLevel one;
    one.Load("../Game2D/res/levels/level1.lvl");
    GameLevel two;
    two.Load("../Game2D/res/levels/level0.lvl");

    this->levels.push_back(one);
    this->levels.push_back(two);
    this->level = 0;

    this->initLevel();
}

void Game::update(float dt) {
    if (this->pengoState == GameState::GAME_ACTIVE) {

        // Check if pengo died (= no lives left, cause he was touched by enemies)
        if (this->levels[this->level].Pengo.lives <= 0) {
            std::cout << "GAME OVER" << std::endl;
            pengoState = GameState::GAME_MENU;
            return;
        }

        // Check if level is completed (= all enemies killed)
        if (this->levels[this->level].IsCompleted()) {
            if (this->level < this->levels.size()) {
                initLevel();
                return;
            }
        }

        this->levels[this->level].updateGameState(dt);
        this->renderer->updateView(dt);
    }
}

void Game::processInput(float dt) {
    if (this->pengoState == GameState::GAME_ACTIVE) {
        if (this->levels[this->level].Pengo.ready) {
            if (this->keys[GLFW_KEY_LEFT_CONTROL]) {
                this->levels[this->level].processPengoAttack();
                return;
            }
            if (this->keys[GLFW_KEY_D]) {
                this->levels[this->level].processPengoMovement(Direction::RIGHT);
                return;
            }
            if (this->keys[GLFW_KEY_A]) {
                this->levels[this->level].processPengoMovement(Direction::LEFT);
                return;
            }
            if (this->keys[GLFW_KEY_W]) {
                this->levels[this->level].processPengoMovement(Direction::UP);
                return;
            }
            if (this->keys[GLFW_KEY_S]) {
                this->levels[this->level].processPengoMovement(Direction::DOWN);
                return;
            }
        }
    }
}

void Game::render() {
    if (this->levels.size() > this->level) {
        this->renderer->drawLevel(this->levels[this->level]);
    }
}


void Game::initLevel() {

    if (this->levels[this->level].Enemies.empty()) {
        this->renderer->blockAnimators.clear();
        this->renderer->enemyAnimators.clear();
        this->levels[this->level].removeObserver(this);
        this->levels[this->level].removeObserver(this->renderer);
        this->levels[this->level].removeObserver(this->soundModule);

        ++this->level;

        if (this->levels.size() <= this->level) {
            std::cout << "GAME WON" << std::endl;
            pengoState = GameState::GAME_MENU;
            return;
        }
        this->carryOverScore();
    }
    this->levels[this->level].registerObserver(this);
    this->levels[this->level].registerObserver(this->renderer);
    this->levels[this->level].registerObserver(this->soundModule);
    this->renderer->initLevelView(&this->levels[this->level]);
    this->levels[this->level].initStates();
}

void Game::update(GameLevel *s) {}

void Game::carryOverScore() {
    this->levels[this->level].score.score = this->levels[this->level - 1].score.score;
}
