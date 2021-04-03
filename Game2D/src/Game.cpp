#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include <array>

// Game-related State data
SpriteRenderer* Renderer;

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

    GameLevel one;
    one.Load("res/levels/level0.lvl", 448, 576);
    this->Levels.push_back(one);
    this->Level = 0;

    // load textures
    //ResourceManager::LoadTexture("res/sprites/Pengo00.bmp","pengo");
}

void Game::Update(float dt)
{

}

void Game::ProcessInput(float dt)
{

}

void Game::Render()
{
    if (this->State == GameState::GAME_ACTIVE)
    {
        // draw level
        this->Levels[this->Level].Draw(*Renderer);
    }

    //Texture2D texture = ResourceManager::GetTexture("pengo");
    //Renderer->DrawSprite(texture, { 6.0f * WIDTH_UNIT, 8.0f * HEIGHT_UNIT });
}