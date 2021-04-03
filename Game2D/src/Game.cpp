#include "Game.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include <array>

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
    ResourceManager::LoadTexture("res/sprites/Pengo00.bmp", "pengo");

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
        float velocityLR = WIDTH_UNIT * dt * 4;
        float velocityUD = HEIGHT_UNIT * dt * 4;
        // move playerboard
        //Movement to the right
        if (P->Position[0] < P->newPosition[0])
        {
            if (P->newPosition[0] - P->Position[0] <= velocityLR)
                P->Position[0] = P->newPosition[0];
            else
                P->Position[0] += velocityLR;
        }
        //Movement to the left
        if (P->Position[0] > P->newPosition[0])
        {
            if (P->newPosition[0] - P->Position[0] >= -velocityLR)
                P->Position[0] = P->newPosition[0];
            else
                P->Position[0] -= velocityLR;
        }
        //Movement up
        if (P->Position[1] < P->newPosition[1])
        {
            if (P->newPosition[1] - P->Position[1] <= velocityUD)
                P->Position[1] = P->newPosition[1];
            else
                P->Position[1] += velocityUD;
        }
        //Movement down
        if (P->Position[1] > P->newPosition[1])
        {
            if (P->newPosition[1] - P->Position[1] >= -velocityUD)
                P->Position[1] = P->newPosition[1];
            else
                P->Position[1] -= velocityUD;
        }
        
        if (P->Position[0] == P->newPosition[0] && P->Position[1] == P->newPosition[1])
        {
            if (this->Keys[GLFW_KEY_D])
            {
                if ((-1.0f + 0.5f * WIDTH_UNIT) + P->Position[0] + WIDTH_UNIT < 1.0f - 0.5f * WIDTH_UNIT)
                    P->newPosition[0] = P->Position[0] + WIDTH_UNIT;
            }
            if (this->Keys[GLFW_KEY_A])
            {
                if ((-1.0f + 0.5f * WIDTH_UNIT) + P->Position[0] - WIDTH_UNIT >= -1.0f + 0.5f * WIDTH_UNIT)
                    P->newPosition[0] = P->Position[0] - WIDTH_UNIT;
            }
            if (this->Keys[GLFW_KEY_W])
            {
                if ((-1.0f + 0.5f * HEIGHT_UNIT) + P->Position[1] + HEIGHT_UNIT < 1.0f - 2 * HEIGHT_UNIT - 0.5f * HEIGHT_UNIT)
                    P->newPosition[1] = P->Position[1] + HEIGHT_UNIT;
            }
            if (this->Keys[GLFW_KEY_S])
            {
                if ((-1.0f + 0.5f * HEIGHT_UNIT) + P->Position[1] - HEIGHT_UNIT >= -1.0f + 0.5f * HEIGHT_UNIT)
                    P->newPosition[1] = P->Position[1] - HEIGHT_UNIT;
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

    //Texture2D texture = ResourceManager::GetTexture("pengo");
    //Renderer->DrawSprite(texture, { 6.0f * WIDTH_UNIT, 8.0f * HEIGHT_UNIT });
}