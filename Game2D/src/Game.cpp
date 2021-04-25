#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include <array>

#include <iostream>
// Game-related State data
SpriteRenderer* Renderer;
Player* P;

Game::Game(unsigned int width, unsigned int height)
    : State(GameState::GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
    delete Renderer;
}

void Game::Init()
{
    // load shaders
    ResourceManager::LoadShader("res/shaders/sprites.vs", "res/shaders/sprites.fs", "sprite");
    // configure shaders
    //glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
    //    static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    // set render-specific controls
    Shader shader = ResourceManager::GetShader("sprite");
    Renderer = new SpriteRenderer(shader);
    // load textures
    ResourceManager::LoadTexture("res/sprites/Iceblock.bmp", "iceblock");
    ResourceManager::LoadTexture("res/sprites/Diamondblock.bmp", "diamondblock");
    ResourceManager::LoadTexture("res/sprites/Wall_LR.bmp", "wallLR");
    ResourceManager::LoadTexture("res/sprites/Wall_BT.bmp", "wallBT");

    //Load all Pengo Textures
    ResourceManager::LoadTexture("res/sprites/PengoRight.bmp", "pengoRight");
    ResourceManager::LoadTexture("res/sprites/PengoLeft.bmp", "pengoLeft");
    ResourceManager::LoadTexture("res/sprites/PengoMoveRight.bmp", "pengoMoveRight");
    ResourceManager::LoadTexture("res/sprites/PengoMoveLeft.bmp", "pengoMoveLeft");
    ResourceManager::LoadTexture("res/sprites/PengoDown.bmp", "pengoDown");
    ResourceManager::LoadTexture("res/sprites/PengoMoveDown.bmp", "pengoMoveDown");
    ResourceManager::LoadTexture("res/sprites/PengoUp.bmp", "pengoUp");
    ResourceManager::LoadTexture("res/sprites/PengoMoveUp.bmp", "pengoMoveUp");

    GameLevel one;
    one.Load("res/levels/level0.lvl", 448, 576);
    P = one.P;
    this->Levels.push_back(one);
    this->Level = 0;
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{
    if (this->State == GameState::GAME_ACTIVE)
    {
        Direction directionBeforeProcessing = P->direction;
        P->move({ WIDTH_UNIT * dt * 4, HEIGHT_UNIT * dt * 4 });
        // move playerboard
        //Movement to the right
        if (P->ready)
        {
            if (this->Keys[GLFW_KEY_D])
            {
                P->setDirection(Direction::RIGHT);
                if (!checkCollisions(Direction::RIGHT))
                {
                    P->calculateMovement();
                    P->swapSprite();
                }
                else if (P->direction != directionBeforeProcessing)
                {
                    P->swapSprite();
                }
                return;
            }
            if (this->Keys[GLFW_KEY_A])
            {
                P->setDirection(Direction::LEFT);
                if (!checkCollisions(Direction::LEFT))
                {
                    P->calculateMovement();
                    P->swapSprite();
                }
                else if (P->direction != directionBeforeProcessing)
                {
                    P->swapSprite();
                }
                return;
            }
            if (this->Keys[GLFW_KEY_W])
            {
                P->setDirection(Direction::UP);
                if (!checkCollisions(Direction::UP))
                {
                    P->calculateMovement();
                    P->swapSprite();
                }
                else if (P->direction != directionBeforeProcessing)
                {
                    P->swapSprite();
                }
                return;
            }
            if (this->Keys[GLFW_KEY_S])
            {
                P->setDirection(Direction::DOWN);
                if (!checkCollisions(Direction::DOWN))
                {
                    P->calculateMovement();
                    P->swapSprite();
                }
                else if (P->direction != directionBeforeProcessing)
                {
                    P->swapSprite();
                }
                return;
            }
        }

        
        //if (this->Keys[GLFW_KEY_D])
        //{
        //    if (Player->Position.x <= this->Width - Player->Size.x)
        //        Player->Position.x += velocity;
        //}
    }
}

void Game::Render()
{
    if (this->State == GameState::GAME_ACTIVE)
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

        //DEBUGGING
        //if (collisionX && collisionY)
        //    std::cout << " 2 Right: " << two.Position[0] + WIDTH_UNIT << " | 1 Left: " << one.Position[0] - WIDTH_UNIT << " | 1 Right: " << one.Position[0] << " | 2 Left: " << two.Position[0] << std::endl;

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
