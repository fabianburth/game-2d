#include "GameLevel.h"

#include <fstream>
#include <sstream>
#include <algorithm>

GameLevel::GameLevel()
{
}

GameLevel::~GameLevel()
{
}

void GameLevel::Load(const char* file, unsigned int levelWidth, unsigned int levelHeight)
{
    // clear old data
    this->Bricks.clear();
    // load from file
    unsigned int tileCode; // (=number of block, e.g. 1 for ice block)
    GameLevel level; 
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> tileData;
    if (fstream)
    {
        while (std::getline(fstream, line)) // read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while (sstream >> tileCode) // read each word separated by spaces
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
            this->init(tileData, levelWidth, levelHeight);
    }
}

//void GameLevel::Draw(SpriteRenderer& renderer)
//{
//    for (GameObject& wall : this->Walls)
//            wall.Draw(renderer);
//
//    for (Block& tile : this->Bricks)
//        if (tile.state != BlockState::BROKEN)
//            tile.Draw(renderer);
//
//    P->Draw(renderer);
//}

bool GameLevel::IsCompleted() // NOT INTENTED TO WORK LIKE THAT FOR PENGO
{
    return this->Enemies.empty();
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
    // calculate dimensions
    std::reverse(tileData.begin(), tileData.end());
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size(); // note we can index vector at [0] since this function is only called if height > 0
    float unit_width = Constants::WIDTH_UNIT, unit_height = Constants::HEIGHT_UNIT;
    LeftWall = Wall(WallSide::LEFT);
    RightWall = Wall(WallSide::RIGHT);
    BottomWall = Wall(WallSide::BOTTOM);
    TopWall = Wall(WallSide::TOP);
    // initialize game information (1P, Score), maybe more later
    //d = GameObject({ (-0.5f * unit_width + width * unit_width) - 0.5f * unit_width , -0.5f * unit_height + 17 * unit_height }, ResourceManager::GetTexture("one"), { 0.5f, 0.5f, (0.5f * (-1 + 0.5f * unit_width)) + 0.5f * unit_width, (0.5f * (-1 + 0.5f * unit_height)) + 0.5f * unit_height});
    P1 = GameInformation({(-0.5f * unit_width + 0.5f * unit_width), -0.5f * unit_height + 17 * unit_height }, { 0.5f, 0.5f, (0.5f * (-1 + 0.5f * unit_width)) + 0.5f * unit_width, (0.5f * (-1 + 0.5f * unit_height)) + 0.5f * unit_height }, 2);
    P1.show("1P");
    Score = GameInformation({ (-0.5f * unit_width + 4.5f * unit_width), -0.5f * unit_height + 17 * unit_height }, { 0.5f, 0.5f, (0.5f * (-1 + 0.5f * unit_width)) + 0.5f * unit_width, (0.5f * (-1 + 0.5f * unit_height)) + 0.5f * unit_height }, 6);
    //Score.show("12345");
    // initialize level wall (same for every level)
    // Left and Right Wall
    for (unsigned int x = 0; x < height + 1; ++x) 
    {
        //Left Wall
        std::array<float, 2> posL = { -0.5f * unit_width, -0.5f * unit_height + unit_height * x };
        std::array<float, 4> sizeL = { 0.5f, 1.0f, 0.5f * (-1 + 0.5f * unit_width), 0 };
        GameObject objL(posL, ResourceManager::GetTexture("wallLR"), sizeL);
        //objL.isUnbreakable = true;
        this->Walls.push_back(objL);
        this->LeftWall.addWallComponent(objL);
        //Right Wall
        std::array<float, 2> posR = { width * unit_width, -0.5f * unit_height + unit_height * x };
        std::array<float, 4> sizeR = { 0.5f, 1.0f, 0.5f * (-1 + 0.5f * unit_width), 0 };
        GameObject objR(posR, ResourceManager::GetTexture("wallLR"), sizeR);
        //objR.isUnbreakable = true;
        this->Walls.push_back(objR);
        this->RightWall.addWallComponent(objR);
    }
    //Bottom and Top Wall
    for (unsigned int x = 0; x < width; ++x)
    {
        //Bottom Wall
        std::array<float, 2> posB = { unit_width * x, height * unit_height};
        std::array<float, 4> sizeB = { 1.0f, 0.5f, 0, 0.5f * (-1 + 0.5f * unit_height) };
        GameObject objB(posB, ResourceManager::GetTexture("wallBT"), sizeB);
        //objB.isUnbreakable = true;
        this->Walls.push_back(objB);
        this->TopWall.addWallComponent(objB);
        //Top Wall
        std::array<float, 2> posT = { unit_width * x, -0.5f * unit_height };
        std::array<float, 4> sizeT = { 1.0f, 0.5f, 0, 0.5f * (-1 + 0.5f * unit_height) };
        GameObject objT(posT, ResourceManager::GetTexture("wallBT"), sizeT);
        //objT.isUnbreakable = true;
        this->Walls.push_back(objT);
        this->BottomWall.addWallComponent(objT);
    }

    // initialize level tiles based on tileData		
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            // check block type from level data (2D level array)
            if (tileData[y][x] == 1) // non-solid iceblock
            {
                std::array<float, 2> pos = { unit_width * x, unit_height * y };
                Block obj(pos, ResourceManager::GetTexture("iceblock"), false, nullptr);
                this->Bricks.push_back(obj);
            }
            else if (tileData[y][x] == 2)	// solid diamond block
            {
                std::array<float, 2> pos = { unit_width * x, unit_height * y };
                Block obj(pos, ResourceManager::GetTexture("diamondblock"), true, nullptr);
                this->Bricks.push_back(obj);
            }
            else if (tileData[y][x] == 3)
            {
                std::array<float, 2> pos = { unit_width * x, unit_height * y };
                std::array<float, 2> velocity = { Constants::WIDTH_UNIT * 3, Constants::HEIGHT_UNIT * 3 };
                Direction direction = Direction::DOWN;
                Enemy* enemy = new Enemy(pos, ResourceManager::GetTexture("enemyMove" + stringDirection(direction) + "00"), velocity, direction, EnemyState::NONE, "Move", false);
                this->frozenEnemies.push_back(enemy);

                Block obj(pos, ResourceManager::GetTexture("iceblock"), false, enemy);
                this->Bricks.push_back(obj);
            }
            else if (tileData[y][x] == 4)
            {
                std::array<float, 2> pos = { unit_width * x, unit_height * y };
                std::array<float, 2> velocity = { Constants::WIDTH_UNIT * 3, Constants::HEIGHT_UNIT * 3 };
                // initial Pengo texture to be loaded
                // to change the texture, P.Sprite has to be changed between rendering
                Pengo = Player(pos, ResourceManager::GetTexture("pengoRight"), velocity);
            }
            else if (tileData[y][x] == 5)
            {
                std::array<float, 2> pos = { unit_width * x, unit_height * y };
                std::array<float, 2> velocity = { Constants::WIDTH_UNIT * 3, Constants::HEIGHT_UNIT * 3};
                Direction direction = Direction::DOWN;
                Enemy* enemy = new Enemy(pos, ResourceManager::GetTexture("enemyMove" + stringDirection(direction) + "00"), velocity, direction, EnemyState::NONE, "Move", false);
                this->Enemies.push_back(enemy);
            }
            else if (tileData[y][x] == 6)
            {
                std::array<float, 2> pos = { unit_width * x, unit_height * y };
                std::array<float, 2> velocity = { Constants::WIDTH_UNIT * 3, Constants::HEIGHT_UNIT * 3 };
                Direction direction = Direction::DOWN;
                Enemy* enemy = new Enemy(pos, ResourceManager::GetTexture("enemyBoxer" + stringDirection(direction) + "00"), velocity, direction, EnemyState::NONE, "Boxer", false);
                this->Enemies.push_back(enemy);
            }
        }
    }
}