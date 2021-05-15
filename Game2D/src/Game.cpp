#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "PengoAnimator.h"
#include "BlockAnimator.h"
#include <array>

#include <iostream>
// Game-related State data
SpriteRenderer* Renderer;
Player* P;
std::shared_ptr<PengoAnimator> pengoAnimator;
std::shared_ptr<BlockAnimator> blockAnimator;

Game::Game(unsigned int width, unsigned int height)
    : PengoState(GameState::GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
    delete Renderer;
    delete P;
}

void Game::Init()
{
    // load shaders
    ResourceManager::LoadShader("res/shaders/sprites.vs", "res/shaders/sprites.fs", "sprite");
    // configure shaders
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    // set render-specific controls
    Shader shader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(shader);
    // load textures
    // Load all Iceblock Textures
    ResourceManager::LoadTexture("res/sprites/Iceblock.bmp", "iceblock");
    ResourceManager::LoadTexture("res/sprites/IceblockBreaking0.bmp", "iceblockBreaking0");
    ResourceManager::LoadTexture("res/sprites/IceblockBreaking1.bmp", "iceblockBreaking1");
    ResourceManager::LoadTexture("res/sprites/IceblockBreaking2.bmp", "iceblockBreaking2");
    ResourceManager::LoadTexture("res/sprites/IceblockBreaking3.bmp", "iceblockBreaking3");

    // Load Diamondblock Textures
    ResourceManager::LoadTexture("res/sprites/Diamondblock.bmp", "diamondblock");

    // Load Wall Textures
    ResourceManager::LoadTexture("res/sprites/Wall_LR.bmp", "wallLR");
    ResourceManager::LoadTexture("res/sprites/Wall_BT.bmp", "wallBT");

    // Load all Pengo Textures
    ResourceManager::LoadTexture("res/sprites/PengoRight.bmp", "pengoRight");
    ResourceManager::LoadTexture("res/sprites/PengoLeft.bmp", "pengoLeft");
    ResourceManager::LoadTexture("res/sprites/PengoMoveRight.bmp", "pengoMoveRight");
    ResourceManager::LoadTexture("res/sprites/PengoMoveLeft.bmp", "pengoMoveLeft");
    ResourceManager::LoadTexture("res/sprites/PengoDown.bmp", "pengoDown");
    ResourceManager::LoadTexture("res/sprites/PengoMoveDown.bmp", "pengoMoveDown");
    ResourceManager::LoadTexture("res/sprites/PengoUp.bmp", "pengoUp");
    ResourceManager::LoadTexture("res/sprites/PengoMoveUp.bmp", "pengoMoveUp");
    ResourceManager::LoadTexture("res/sprites/PengoPushRight.bmp", "pengoPushRight");
    ResourceManager::LoadTexture("res/sprites/PengoPushLeft.bmp", "pengoPushLeft");
    ResourceManager::LoadTexture("res/sprites/PengoPushUp.bmp", "pengoPushUp");
    ResourceManager::LoadTexture("res/sprites/PengoPushUpMove.bmp", "pengoPushUpMove");
    ResourceManager::LoadTexture("res/sprites/PengoPushDown.bmp", "pengoPushDown");
    ResourceManager::LoadTexture("res/sprites/PengoPushDownMove.bmp", "pengoPushDownMove");
    ResourceManager::LoadTexture("res/sprites/PengoPostPushLeft.bmp", "pengoPostPushLeft");
    ResourceManager::LoadTexture("res/sprites/PengoPostPushRight.bmp", "pengoPostPushRight");

    GameLevel one;
    one.Load("res/levels/level0.lvl", 448, 576);
    P = one.P;
    this->Levels.push_back(one);
    this->Level = 0;

    pengoAnimator = std::make_shared<PengoAnimator>(P, 0.5f, 0.25f);
    blockAnimator = std::make_shared<BlockAnimator>(0.5f);
    P->addObserver(pengoAnimator);

    for (GameObject& tile : this->Levels[this->Level].Bricks)
        tile.addObserver(blockAnimator);
}

void Game::Update(float dt)
{
    // Update Players actual position
    P->move({ WIDTH_UNIT * dt * 4, HEIGHT_UNIT * dt * 4 });
    pengoAnimator->animate(dt);
    blockAnimator->animate(dt);
}

void Game::ProcessInput(float dt)
{
    if (this->PengoState == GameState::GAME_ACTIVE)
    {
        if (P->ready)
        {
            if (this->Keys[GLFW_KEY_LEFT_CONTROL])
            {
                if (doCollision(P->direction))
                {
                    P->setState(PengoState::PUSH);
                }
                return;
            }
            if (this->Keys[GLFW_KEY_D])
            {
                P->setDirection(Direction::RIGHT);
                P->setState(PengoState::WALK);
                if (!checkCollisions(Direction::RIGHT))
                {
                    P->calculateMovement();
                }
                return;
            }
            if (this->Keys[GLFW_KEY_A])
            {
                P->setDirection(Direction::LEFT);
                P->setState(PengoState::WALK);
                if (!checkCollisions(Direction::LEFT))
                {
                    P->calculateMovement();
                }
                return;
            }
            if (this->Keys[GLFW_KEY_W])
            {
                P->setDirection(Direction::UP);
                P->setState(PengoState::WALK);
                if (!checkCollisions(Direction::UP))
                {
                    P->calculateMovement();
                }
                return;
            }
            if (this->Keys[GLFW_KEY_S])
            {
                P->setDirection(Direction::DOWN);
                P->setState(PengoState::WALK);
                if (!checkCollisions(Direction::DOWN))
                {
                    P->calculateMovement();
                }
                return;
            }
        }
    }
}

void Game::Render()
{
    if (this->PengoState == GameState::GAME_ACTIVE)
    {
        // draw level
        this->Levels[this->Level].Draw(*Renderer);
    }

    // Texture2D texture = ResourceManager::GetTexture("pengo");
    // Renderer->DrawSprite(texture, { 6.0f * WIDTH_UNIT, 8.0f * HEIGHT_UNIT });
}

bool Game::checkCollisionRight(GameObject& one, GameObject& two)
{
    //collision with right wall
    if (!((-1.0f + 0.5f * WIDTH_UNIT) + P->Position[0] + WIDTH_UNIT < 1.0f - 0.5f * WIDTH_UNIT))
    {
        return true;
    }
    else
    {
        // collision x-axis
        bool collisionX = ((one.Position[0] + 2 * WIDTH_UNIT) - two.Position[0]) > EPSILON && ((two.Position[0] + WIDTH_UNIT) - (one.Position[0] + WIDTH_UNIT)) > EPSILON;
        // collision y-axis
        bool collisionY = ((one.Position[1] + HEIGHT_UNIT) - two.Position[1]) > EPSILON && ((two.Position[1] + HEIGHT_UNIT) - one.Position[1]) > EPSILON;
        // collision only if on both axes
        return collisionX && collisionY;
    }
}

bool Game::checkCollisionLeft(GameObject& one, GameObject& two)
{
    //collision with left wall
    if (!((-1.0f + 0.5f * WIDTH_UNIT) + P->Position[0] - WIDTH_UNIT >= -1.0f + 0.5f * WIDTH_UNIT))
    {
        return true;
    }
    else
    {
        // collision x-axis
        bool collisionX = ((one.Position[0] + WIDTH_UNIT - WIDTH_UNIT) - two.Position[0]) > EPSILON && ((two.Position[0] + WIDTH_UNIT) - (one.Position[0] - WIDTH_UNIT)) > EPSILON;
        // collision y-axis
        bool collisionY = ((one.Position[1] + HEIGHT_UNIT) - two.Position[1]) > EPSILON && ((two.Position[1] + HEIGHT_UNIT) - one.Position[1]) > EPSILON;
        // collision only if on both axes
        return collisionX && collisionY;
    }
}

bool Game::checkCollisionUp(GameObject& one, GameObject& two)
{
    // collision with top wall
    if (!((-1.0f + 0.5f * HEIGHT_UNIT) + P->Position[1] + HEIGHT_UNIT < 1.0f - 2 * HEIGHT_UNIT - 0.5f * HEIGHT_UNIT))
    {
        return true;
    }
    else
    {
        // collision x-axis
        bool collisionX = ((one.Position[0] + WIDTH_UNIT) - two.Position[0]) > EPSILON && ((two.Position[0] + WIDTH_UNIT) - one.Position[0]) > EPSILON;
        // collision y-axis
        bool collisionY = ((one.Position[1] + 2 * HEIGHT_UNIT) - two.Position[1]) > EPSILON && ((two.Position[1] + HEIGHT_UNIT) - (one.Position[1] + HEIGHT_UNIT)) > EPSILON;
        // collision only if on both axes
        return collisionX && collisionY;
    }
}

bool Game::checkCollisionDown(GameObject& one, GameObject& two)
{
    // collision bottom wall
    if (!((-1.0f + 0.5f * HEIGHT_UNIT) + P->Position[1] - HEIGHT_UNIT >= -1.0f + 0.5f * HEIGHT_UNIT)) 
    {
        return true;
    }
    else
    {
        // collision x-axis
        bool collisionX = ((one.Position[0] + WIDTH_UNIT) - two.Position[0]) > EPSILON && ((two.Position[0] + WIDTH_UNIT) - one.Position[0]) > EPSILON;
        // collision y-axis
        bool collisionY = ((one.Position[1] + HEIGHT_UNIT - HEIGHT_UNIT) - two.Position[1]) > EPSILON && ((two.Position[1] + HEIGHT_UNIT) - (one.Position[1] - HEIGHT_UNIT)) > EPSILON;
        // collision only if on both axes
        return collisionX && collisionY;
    }
}


bool Game::checkCollisions(Direction d)
{
    for (GameObject& block : this->Levels[this->Level].Bricks)
    {
        if (!block.Destroyed)
        {
            if (d == Direction::RIGHT && checkCollisionRight(*P, block)
                || d == Direction::LEFT && checkCollisionLeft(*P, block)
                || d == Direction::UP && checkCollisionUp(*P, block)
                || d == Direction::DOWN && checkCollisionDown(*P, block))
            {
                return true;
            }
        }
    }
    return false;
}

bool Game::doCollision(Direction d)
{
    for (GameObject& block : this->Levels[this->Level].Bricks)
    {
        if (!block.Destroyed)
        {
            if (d == Direction::RIGHT && checkCollisionRight(*P, block)
                || d == Direction::LEFT && checkCollisionLeft(*P, block)
                || d == Direction::UP && checkCollisionUp(*P, block)
                || d == Direction::DOWN && checkCollisionDown(*P, block))
            {
                if (!block.IsSolid)
                    block.destroy();
                return true;
            }
        }
    }
    return false;
}


