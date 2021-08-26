#include "GameLevel.h"

#include <fstream>
#include <sstream>
#include <algorithm>

GameLevel::GameLevel() {
}

GameLevel::~GameLevel() {
}

void GameLevel::Load(const char *file, unsigned int levelWidth, unsigned int levelHeight) {
    // clear old data
    this->Bricks.clear();
    // load from file
    unsigned int tileCode; // (=number of block, e.g. 1 for ice block)
    GameLevel level;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> tileData;
    if (fstream) {
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

void
GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight) {
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
    this->score = 0;
    P1 = GameInformation({(-0.5f * unit_width + 0.5f * unit_width), -0.5f * unit_height + 17 * unit_height},
                         {0.5f, 0.5f, (0.5f * (-1 + 0.5f * unit_width)) + 0.5f * unit_width,
                          (0.5f * (-1 + 0.5f * unit_height)) + 0.5f * unit_height}, 2);
    P1.show("1P");
    Score = GameInformation({(-0.5f * unit_width + 4.5f * unit_width), -0.5f * unit_height + 17 * unit_height},
                            {0.5f, 0.5f, (0.5f * (-1 + 0.5f * unit_width)) + 0.5f * unit_width,
                             (0.5f * (-1 + 0.5f * unit_height)) + 0.5f * unit_height}, 6);
    //Score.show("12345");
    // initialize level wall (same for every level)
    // Left and Right Wall
    for (unsigned int x = 0; x < height + 1; ++x) {
        //Left Wall
        std::array<float, 2> posL = {-0.5f * unit_width, -0.5f * unit_height + unit_height * x};
        std::array<float, 4> sizeL = {0.5f, 1.0f, 0.5f * (-1 + 0.5f * unit_width), 0};
        GameObject objL(posL, ResourceManager::GetTexture("wallLR"), sizeL);
        //objL.isUnbreakable = true;
        this->Walls.push_back(objL);
        this->LeftWall.addWallComponent(objL);
        //Right Wall
        std::array<float, 2> posR = {width * unit_width, -0.5f * unit_height + unit_height * x};
        std::array<float, 4> sizeR = {0.5f, 1.0f, 0.5f * (-1 + 0.5f * unit_width), 0};
        GameObject objR(posR, ResourceManager::GetTexture("wallLR"), sizeR);
        //objR.isUnbreakable = true;
        this->Walls.push_back(objR);
        this->RightWall.addWallComponent(objR);
    }
    //Bottom and Top Wall
    for (unsigned int x = 0; x < width; ++x) {
        //Bottom Wall
        std::array<float, 2> posB = {unit_width * x, height * unit_height};
        std::array<float, 4> sizeB = {1.0f, 0.5f, 0, 0.5f * (-1 + 0.5f * unit_height)};
        GameObject objB(posB, ResourceManager::GetTexture("wallBT"), sizeB);
        //objB.isUnbreakable = true;
        this->Walls.push_back(objB);
        this->TopWall.addWallComponent(objB);
        //Top Wall
        std::array<float, 2> posT = {unit_width * x, -0.5f * unit_height};
        std::array<float, 4> sizeT = {1.0f, 0.5f, 0, 0.5f * (-1 + 0.5f * unit_height)};
        GameObject objT(posT, ResourceManager::GetTexture("wallBT"), sizeT);
        //objT.isUnbreakable = true;
        this->Walls.push_back(objT);
        this->BottomWall.addWallComponent(objT);
    }

    // initialize level tiles based on tileData		
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            // check block type from level data (2D level array)
            if (tileData[y][x] == 1) // non-solid iceblock
            {
                std::array<float, 2> pos = {unit_width * x, unit_height * y};
                Block obj(pos, ResourceManager::GetTexture("iceblock"), false, nullptr);
                this->Bricks.push_back(obj);
            } else if (tileData[y][x] == 2)    // solid diamond block
            {
                std::array<float, 2> pos = {unit_width * x, unit_height * y};
                Block obj(pos, ResourceManager::GetTexture("diamondblock"), true, nullptr);
                this->Bricks.push_back(obj);
            } else if (tileData[y][x] == 3) {
                std::array<float, 2> pos = {unit_width * x, unit_height * y};
                std::array<float, 2> velocity = {Constants::WIDTH_UNIT * 3, Constants::HEIGHT_UNIT * 3};
                Direction direction = Direction::DOWN;
                Enemy *enemy = new Enemy(pos,
                                         ResourceManager::GetTexture("enemyMove" + stringDirection(direction) + "00"),
                                         velocity, direction, EnemyState::NONE, "Move", false);
                this->frozenEnemies.push_back(enemy);

                Block obj(pos, ResourceManager::GetTexture("iceblock"), false, enemy);
                this->Bricks.push_back(obj);
            } else if (tileData[y][x] == 4) {
                std::array<float, 2> pos = {unit_width * x, unit_height * y};
                std::array<float, 2> velocity = {Constants::WIDTH_UNIT * 3, Constants::HEIGHT_UNIT * 3};
                // initial Pengo texture to be loaded
                // to change the texture, P.Sprite has to be changed between rendering
                Pengo = Player(pos, ResourceManager::GetTexture("pengoRight"), velocity);
            } else if (tileData[y][x] == 5) {
                std::array<float, 2> pos = {unit_width * x, unit_height * y};
                std::array<float, 2> velocity = {Constants::WIDTH_UNIT * 3, Constants::HEIGHT_UNIT * 3};
                Direction direction = Direction::DOWN;
                Enemy *enemy = new Enemy(pos,
                                         ResourceManager::GetTexture("enemyMove" + stringDirection(direction) + "00"),
                                         velocity, direction, EnemyState::NONE, "Move", false);
                this->Enemies.push_back(enemy);
            } else if (tileData[y][x] == 6) {
                std::array<float, 2> pos = {unit_width * x, unit_height * y};
                std::array<float, 2> velocity = {Constants::WIDTH_UNIT * 3, Constants::HEIGHT_UNIT * 3};
                Direction direction = Direction::DOWN;
                Enemy *enemy = new Enemy(pos,
                                         ResourceManager::GetTexture("enemyBoxer" + stringDirection(direction) + "00"),
                                         velocity, direction, EnemyState::NONE, "Boxer", false);
                this->Enemies.push_back(enemy);
            }
        }
    }
}

bool GameLevel::checkCollisions(GameObject &gameObject, Direction d) {
    for (Block &block : this->Bricks) {
        if (block.state != BlockState::BROKEN) {
            if (checkBlockCollision(gameObject, block, d) || checkWallCollision(gameObject, d)) {
                return true;
            }
        }
    }
    return false;
}

bool GameLevel::checkBlockCollision(GameObject &one, GameObject &two, Direction d) {
    bool collisionX = false;
    bool collisionY = false;

    switch (d) {
        case Direction::RIGHT:
            collisionX = ((one.position[0] + 2 * Constants::WIDTH_UNIT) - two.position[0]) > Constants::EPSILON &&
                         ((two.position[0] + Constants::WIDTH_UNIT) - (one.position[0] + Constants::WIDTH_UNIT)) >
                         Constants::EPSILON;
            collisionY = ((one.position[1] + Constants::HEIGHT_UNIT) - two.position[1]) > Constants::EPSILON &&
                         ((two.position[1] + Constants::HEIGHT_UNIT) - one.position[1]) > Constants::EPSILON;
            break;
        case Direction::LEFT:
            collisionX =
                    ((one.position[0] + Constants::WIDTH_UNIT - Constants::WIDTH_UNIT) - two.position[0]) >
                    Constants::EPSILON &&
                    ((two.position[0] + Constants::WIDTH_UNIT) - (one.position[0] - Constants::WIDTH_UNIT)) >
                    Constants::EPSILON;
            collisionY = ((one.position[1] + Constants::HEIGHT_UNIT) - two.position[1]) > Constants::EPSILON &&
                         ((two.position[1] + Constants::HEIGHT_UNIT) - one.position[1]) > Constants::EPSILON;
            break;
        case Direction::UP:
            collisionX = ((one.position[0] + Constants::WIDTH_UNIT) - two.position[0]) > Constants::EPSILON &&
                         ((two.position[0] + Constants::WIDTH_UNIT) - one.position[0]) > Constants::EPSILON;
            collisionY = ((one.position[1] + 2 * Constants::HEIGHT_UNIT) - two.position[1]) > Constants::EPSILON &&
                         ((two.position[1] + Constants::HEIGHT_UNIT) - (one.position[1] + Constants::HEIGHT_UNIT)) >
                         Constants::EPSILON;
            break;
        case Direction::DOWN:
            collisionX = ((one.position[0] + Constants::WIDTH_UNIT) - two.position[0]) > Constants::EPSILON &&
                         ((two.position[0] + Constants::WIDTH_UNIT) - one.position[0]) > Constants::EPSILON;
            collisionY =
                    ((one.position[1] + Constants::HEIGHT_UNIT - Constants::HEIGHT_UNIT) - two.position[1]) >
                    Constants::EPSILON &&
                    ((two.position[1] + Constants::HEIGHT_UNIT) - (one.position[1] - Constants::HEIGHT_UNIT)) >
                    Constants::EPSILON;
            break;
    }
    return collisionX && collisionY;
}

bool GameLevel::checkWallCollision(GameObject &one, Direction d) {
    bool collision = false;

    switch (d) {
        case Direction::RIGHT:
            //collision = !((-1.0f + 0.5f * Constants::WIDTH_UNIT) + one.position[0] + Constants::WIDTH_UNIT < 1.0f - 0.5f * Constants::WIDTH_UNIT );
            collision = !(((one.position[0] + Constants::WIDTH_UNIT) - (12 * Constants::WIDTH_UNIT)) < Constants::EPSILON);
            break;
        case Direction::LEFT:
            //collision = !((-1.0f + 0.5f * Constants::WIDTH_UNIT) + one.position[0] - Constants::WIDTH_UNIT >= -1.0f + 0.5f * Constants::WIDTH_UNIT);
            collision = !(0 - (one.position[0] - Constants::WIDTH_UNIT) < Constants::EPSILON);
            break;
        case Direction::UP:
            //collision = !((-1.0f + 0.5f * Constants::HEIGHT_UNIT) + one.position[1] + Constants::HEIGHT_UNIT < 1.0f - 2 * Constants::HEIGHT_UNIT - 0.5f * Constants::HEIGHT_UNIT);
            collision = !(((one.position[1] + Constants::HEIGHT_UNIT) - (14 * Constants::HEIGHT_UNIT)) < Constants::EPSILON);
            break;
        case Direction::DOWN:
            //collision = !((-1.0f + 0.5f * Constants::HEIGHT_UNIT) + one.position[1] - Constants::HEIGHT_UNIT >= (-1.0f + 0.5f * Constants::HEIGHT_UNIT));
            collision = !(0 - (one.position[1] - Constants::HEIGHT_UNIT) < Constants::EPSILON);
            break;
    }
    return collision;
}

Block *GameLevel::getCollisionBlock(GameObject &gameObject, Direction d) {
    for (Block &block : this->Bricks) {
        if (block.state != BlockState::BROKEN) {
            if (checkBlockCollision(gameObject, block, d)) {
                return &block;
            }
        }
    }
    return nullptr;
}

int GameLevel::calculateStepRange(Block &block, Direction d) {
    int stepWidth = 0;
    std::array<float, 2> originalPosition = block.position;

    while (!checkCollisions(block, d)) {
        block.setPositionToMoveTo(d);
        block.position = block.positionToMoveTo;
        stepWidth++;
    }

    block.position = originalPosition;
    return stepWidth;
}

bool GameLevel::checkWallCollisionPrecise(GameObject &one, Direction d) {
    bool collision = false;

    switch (d) {
        case Direction::RIGHT:
            //collision = !((-1.0f + 0.5f * Constants::WIDTH_UNIT) + one.position[0] + Constants::WIDTH_UNIT < 1.0f - 0.5f * Constants::WIDTH_UNIT );
            collision = !(((12 * Constants::WIDTH_UNIT) - one.position[0]) > Constants::EPSILON);
            break;
        case Direction::LEFT:
            //collision = !((-1.0f + 0.5f * Constants::WIDTH_UNIT) + one.position[0] - Constants::WIDTH_UNIT >= -1.0f + 0.5f * Constants::WIDTH_UNIT);
            collision = !(0 + one.position[0] > Constants::EPSILON);
            break;
        case Direction::UP:
            //collision = !((-1.0f + 0.5f * Constants::HEIGHT_UNIT) + one.position[1] + Constants::HEIGHT_UNIT < 1.0f - 2 * Constants::HEIGHT_UNIT - 0.5f * Constants::HEIGHT_UNIT);
            collision = !(((14 * Constants::HEIGHT_UNIT) - one.position[1]) > Constants::EPSILON);
            break;
        case Direction::DOWN:
            //collision = !((-1.0f + 0.5f * Constants::HEIGHT_UNIT) + one.position[1] - Constants::HEIGHT_UNIT >= (-1.0f + 0.5f * Constants::HEIGHT_UNIT));
            collision = !(0 + one.position[1] > Constants::EPSILON);
            break;
    }
    return collision;
}

bool GameLevel::checkCollisionPrecise(GameObject &one, GameObject &two) {
    bool collisionX =
            one.position[0] + Constants::WIDTH_UNIT - two.position[0] > Constants::EPSILON && two.position[0] + Constants::WIDTH_UNIT - one.position[0] > Constants::EPSILON;
    bool collisionY =
            one.position[1] + Constants::HEIGHT_UNIT - two.position[1] > Constants::EPSILON && two.position[1] + Constants::HEIGHT_UNIT - one.position[1] > Constants::EPSILON;
    return collisionX && collisionY;
}


// ----------------------------------------------------------------------------
// Methods to determine enemy behavior
// ----------------------------------------------------------------------------
std::vector<Direction> GameLevel::getInitialDirections(Enemy &enemy) {

    // Build array for determining a direction with certain propabilities
    std::vector<Direction> allDirections{Direction::RIGHT, Direction::LEFT, Direction::UP, Direction::DOWN};
    std::vector<Direction> orderedDirections;
    std::vector<Direction> directions;

    float xDistance = std::abs(enemy.position[0] - Pengo.position[0]) * (2.0f / 448.0f);
    float yDistance = std::abs(enemy.position[1] - Pengo.position[1]) * (2.0f / 576.0f);

    switch (enemy.state) {
        case EnemyState::WANDERING:
            orderedDirections.push_back(enemy.direction);
            for (Direction d : allDirections) {
                if (d != enemy.direction && d != oppositeDirection(enemy.direction)) {
                    orderedDirections.push_back(d);
                }
            }
            orderedDirections.push_back(oppositeDirection(enemy.direction));

            for (int i = 0; i < orderedDirections.size(); ++i) {
                if (!checkCollisions(enemy, orderedDirections.at(i))) {
                    directions.push_back(orderedDirections.at(i));
                }
            }
            break;
        case EnemyState::CHASING:

            if (xDistance >= yDistance) {
                //Move horizontally (x-direction)
                if (enemy.position[0] > Pengo.position[0]) {
                    //Pengo is left, so move left
                    orderedDirections.push_back(Direction::LEFT);
                } else {
                    orderedDirections.push_back(Direction::RIGHT);
                }

                if (enemy.position[1] > Pengo.position[1]) {
                    //Pengo is left, so move left
                    orderedDirections.push_back(Direction::DOWN);
                } else {
                    orderedDirections.push_back(Direction::UP);
                }
            } else if (xDistance < yDistance) {
                //Move vertically (y-direction)
                if (enemy.position[1] > Pengo.position[1]) {
                    //Pengo is left, so move left
                    orderedDirections.push_back(Direction::DOWN);
                } else {
                    orderedDirections.push_back(Direction::UP);
                }

                if (enemy.position[0] > Pengo.position[0]) {
                    //Pengo is left, so move left
                    orderedDirections.push_back(Direction::LEFT);
                } else {
                    orderedDirections.push_back(Direction::RIGHT);
                }
            }

            for (Direction d : allDirections) {
                if (std::find(orderedDirections.begin(), orderedDirections.end(), d) == orderedDirections.end()) {
                    orderedDirections.push_back(d);
                }
            }

            for (int i = 0; i < orderedDirections.size(); ++i) {
                if (!checkWallCollision(enemy, orderedDirections.at(i))) {
                    Block *block = getCollisionBlock(enemy, orderedDirections.at(i));
                    if (block == nullptr || !block->isUnbreakable) {
                        directions.push_back(orderedDirections.at(i));
                    }
                }
            }
            break;
    }

    return directions;
}

int GameLevel::getDirectionIndex(std::vector<int> chances) {
    int index = 0;
    int randomNumber = std::rand() % 100;
    for (int i = 0; i < chances.size(); i++) {
        if (randomNumber > chances.at(i))
            index++;
    }
    return index;
}
// ----------------------------------------------------------------------------


bool GameLevel::checkThreeDiamonds() {
    int amountAdjacentDiamonds = 0;
    bool bTouchesWall = false;
    bool firstAdjacentBlockTouchesWall = false;
    bool secondAdjacentBlockTouchesWall = false;

    for (Block& b : this->Bricks)
    {
        if (b.isUnbreakable)
        {
            bTouchesWall = blockTouchesWall(b);
            Block* firstAdjacentBlock = getCollisionBlock(b, Direction::RIGHT);
            if (firstAdjacentBlock != nullptr && firstAdjacentBlock->isUnbreakable)
            {
                Block fab = *firstAdjacentBlock;
                firstAdjacentBlockTouchesWall = blockTouchesWall(fab);
                Block* secondAdjacentBlock = getCollisionBlock(fab, Direction::RIGHT);
                if (secondAdjacentBlock != nullptr && secondAdjacentBlock->isUnbreakable)
                {
                    Block sab = *secondAdjacentBlock;
                    secondAdjacentBlockTouchesWall = blockTouchesWall(sab);
                    if (bTouchesWall || firstAdjacentBlockTouchesWall || secondAdjacentBlockTouchesWall)
                        score += 5000;
                    else
                        score += 10000;
                    return true;
                }
            }
            //bTouchesWall = checkWallCollision(b, Direction::LEFT);
            firstAdjacentBlock = getCollisionBlock(b, Direction::LEFT);
            if (firstAdjacentBlock != nullptr && firstAdjacentBlock->isUnbreakable)
            {
                Block fab = *firstAdjacentBlock;
                firstAdjacentBlockTouchesWall = blockTouchesWall(fab);
                Block* secondAdjacentBlock = getCollisionBlock(fab, Direction::LEFT);
                if (secondAdjacentBlock != nullptr && secondAdjacentBlock->isUnbreakable)
                {
                    Block sab = *secondAdjacentBlock;
                    secondAdjacentBlockTouchesWall = blockTouchesWall(sab);
                    if (bTouchesWall || firstAdjacentBlockTouchesWall || secondAdjacentBlockTouchesWall)
                        score += 5000;
                    else
                        score += 10000;
                    return true;
                }
            }
            //bTouchesWall = checkWallCollision(b, Direction::UP);
            firstAdjacentBlock = getCollisionBlock(b, Direction::UP);
            if (firstAdjacentBlock != nullptr && firstAdjacentBlock->isUnbreakable)
            {
                Block fab = *firstAdjacentBlock;
                firstAdjacentBlockTouchesWall = blockTouchesWall(fab);
                Block* secondAdjacentBlock = getCollisionBlock(fab, Direction::UP);
                if (secondAdjacentBlock != nullptr && secondAdjacentBlock->isUnbreakable)
                {
                    Block sab = *secondAdjacentBlock;
                    secondAdjacentBlockTouchesWall = blockTouchesWall(sab);
                    if (bTouchesWall || firstAdjacentBlockTouchesWall || secondAdjacentBlockTouchesWall)
                        score += 5000;
                    else
                        score += 10000;
                    return true;
                }
            }
            //bTouchesWall = checkWallCollision(b, Direction::DOWN);
            firstAdjacentBlock = getCollisionBlock(b, Direction::DOWN);
            if (firstAdjacentBlock != nullptr && firstAdjacentBlock->isUnbreakable)
            {
                Block fab = *firstAdjacentBlock;
                firstAdjacentBlockTouchesWall = blockTouchesWall(fab);
                Block* secondAdjacentBlock = getCollisionBlock(fab, Direction::DOWN);
                if (secondAdjacentBlock != nullptr && secondAdjacentBlock->isUnbreakable)
                {
                    Block sab = *secondAdjacentBlock;
                    secondAdjacentBlockTouchesWall = blockTouchesWall(sab);
                    if (bTouchesWall || firstAdjacentBlockTouchesWall || secondAdjacentBlockTouchesWall)
                        score += 5000;
                    else
                        score += 10000;
                    return true;
                }
            }
        }
    }
    return false;
}

bool GameLevel::blockTouchesWall(Block &b) {
    return checkWallCollision(b, Direction::RIGHT) || checkWallCollision(b, Direction::LEFT) || checkWallCollision(b, Direction::UP) || checkWallCollision(b, Direction::DOWN);
}
