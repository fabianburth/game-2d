#include "gamelevel.h"

#include <fstream>
#include <sstream>

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

void GameLevel::Draw(SpriteRenderer& renderer)
{
    for (GameObject& wall : this->Walls)
            wall.Draw(renderer);

    for (GameObject& tile : this->Bricks)
        if (!tile.Destroyed)
            tile.Draw(renderer);

    P->Draw(renderer);
}

bool GameLevel::IsCompleted() // NOT INTENTED TO WORK LIKE THAT FOR PENGO
{
    for (GameObject& tile : this->Bricks)
        if (!tile.IsSolid && !tile.Destroyed)
            return false;
    return true;
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
    // calculate dimensions
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size(); // note we can index vector at [0] since this function is only called if height > 0
    float unit_width = WIDTH_UNIT, unit_height = HEIGHT_UNIT;
    //initialize level wall (same for every level)
    //Left and Right Wall
    for (unsigned int x = 0; x < height + 1; ++x) 
    {
        //Left Wall
        std::array<float, 2> posL = { -0.5f * unit_width, -0.5f * unit_height + unit_height * x };
        std::array<float, 4> sizeL = { 0.5f, 1.0f, 0.5f * (-1 + 0.5f * unit_width), 0 };
        GameObject objL(posL, sizeL, ResourceManager::GetTexture("wallLR"), { 0.8f, 0.8f, 0.7f });
        objL.IsSolid = true;
        this->Walls.push_back(objL);
        //Right Wall
        std::array<float, 2> posR = { width * unit_width, -0.5f * unit_height + unit_height * x };
        std::array<float, 4> sizeR = { 0.5f, 1.0f, 0.5f * (-1 + 0.5f * unit_width), 0 };
        GameObject objR(posR, sizeR, ResourceManager::GetTexture("wallLR"), { 0.8f, 0.8f, 0.7f });
        objR.IsSolid = true;
        this->Walls.push_back(objR);
    }
    //Bottom and Top Wall
    for (unsigned int x = 0; x < width; ++x)
    {
        //Bottom Wall
        std::array<float, 2> posB = { unit_width * x, height * unit_height};
        std::array<float, 4> sizeB = { 1.0f, 0.5f, 0, 0.5f * (-1 + 0.5f * unit_height) };
        GameObject objB(posB, sizeB, ResourceManager::GetTexture("wallBT"), { 0.8f, 0.8f, 0.7f });
        objB.IsSolid = true;
        this->Walls.push_back(objB);
        //Top Wall
        std::array<float, 2> posT = { unit_width * x, -0.5f * unit_height };
        std::array<float, 4> sizeT = { 1.0f, 0.5f, 0, 0.5f * (-1 + 0.5f * unit_height) };
        GameObject objT(posT, sizeT, ResourceManager::GetTexture("wallBT"), { 0.8f, 0.8f, 0.7f });
        objT.IsSolid = true;
        this->Walls.push_back(objT);
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
                std::array<float, 4> size = { 1.0f, 1.0f, 0.0f, 0.0f };
                GameObject obj(pos, size, ResourceManager::GetTexture("iceblock"), { 0.8f, 0.8f, 0.7f });
                obj.IsSolid = false;
                this->Bricks.push_back(obj);
            }
            else if (tileData[y][x] == 2)	// solid diamond block
            {
                std::array<float, 2> pos = { unit_width * x, unit_height * y };
                std::array<float, 4> size = { 1.0f, 1.0f, 0.0f, 0.0f };
                this->Bricks.push_back(GameObject(pos, size, ResourceManager::GetTexture("diamondblock"), { 0.8f, 0.8f, 0.7f }));
            }
            else if (tileData[y][x] == 4)
            {
                std::array<float, 2> pos = { unit_width * x, unit_height * y };
                std::array<float, 4> size = { 1.0f, 1.0f, 0.0f, 0.0f };
                // initial Pengo texture to be loaded
                // to change the texture, P.Sprite has to be changed between rendering
                P = new Player(pos, size, ResourceManager::GetTexture("pengoRight"));
            }
        }
    }
}