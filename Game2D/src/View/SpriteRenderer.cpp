#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Shader &shader) : shader(shader) {
    this->initRenderData();

    this->initDisplayInformation();
    this->loadSprites();
}

SpriteRenderer::~SpriteRenderer() {
    glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::drawSprite(Texture2D &texture, std::array<float, 2> position, std::array<float, 4> size,
                                std::array<float, 3> color) {
    // prepare transformations
    this->shader.use();

    // the first 2 elements of size are the scaling values for x and y
    // the other 2 elements are the values to correct the position when scaling
    this->shader.setVector4f("size", size[0], size[1], size[2], size[3]);
    this->shader.setVector2f("position", position[0], position[1]);
    // render textured quad
    this->shader.setVector3f("spriteColor", color[0], color[1], color[2]);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::drawLevel(GameLevel &gameLevel) {
    for (GameObject &wall : leftWallAnimator->wall->wallComponents)
        this->drawSprite(leftWallAnimator->sprite, wall.position, wall.size);

    for (GameObject &wall : rightWallAnimator->wall->wallComponents)
        this->drawSprite(rightWallAnimator->sprite, wall.position, wall.size);

    for (GameObject &wall : topWallAnimator->wall->wallComponents)
        this->drawSprite(topWallAnimator->sprite, wall.position, wall.size);

    for (GameObject &wall : bottomWallAnimator->wall->wallComponents)
        this->drawSprite(bottomWallAnimator->sprite, wall.position, wall.size);

    for (BlockAnimator *blockAnimator : blockAnimators)
        if (blockAnimator->block->state != BlockState::BROKEN)
            this->drawSprite(blockAnimator->sprite, blockAnimator->block->position, blockAnimator->block->size);

    for (EnemyAnimator *enemyAnimator : enemyAnimators)
        this->drawSprite(enemyAnimator->sprite, enemyAnimator->enemy->position, enemyAnimator->enemy->size);

    this->drawSprite(pengoAnimator->sprite, pengoAnimator->pengo->position, pengoAnimator->pengo->size);
    this->P1.show("1P");
    this->DrawDisplayElement(this->P1);
    this->Score.show(std::to_string(gameLevel.score.score));
    this->DrawDisplayElement(this->Score);
}

void SpriteRenderer::initRenderData() {
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = {
            // clang-format off
            // pos                                                                                                                            // tex
            //x                                                             //y
            -1.0f + 0.5f * Constants::WIDTH_UNIT,                           -1.0f + 0.5f * Constants::HEIGHT_UNIT,                            0.0f, 0.0f, //bottom-left
            -1.0f + 0.5f * Constants::WIDTH_UNIT,                           -1.0f + 0.5f * Constants::HEIGHT_UNIT + Constants::HEIGHT_UNIT,   0.0f, 1.0f, //top-left
            -1.0f + 0.5f * Constants::WIDTH_UNIT + Constants::WIDTH_UNIT,   -1.0f + 0.5f * Constants::HEIGHT_UNIT,                            1.0f, 0.0f, //bottom-right

            -1.0f + 0.5f * Constants::WIDTH_UNIT,                           -1.0f + 0.5f * Constants::HEIGHT_UNIT + Constants::HEIGHT_UNIT,   0.0f, 1.0f, //top-left
            -1.0f + 0.5f * Constants::WIDTH_UNIT + Constants::WIDTH_UNIT,   -1.0f + 0.5f * Constants::HEIGHT_UNIT + Constants::HEIGHT_UNIT,   1.0f, 1.0f, //top-right
            -1.0f + 0.5f * Constants::WIDTH_UNIT + Constants::WIDTH_UNIT,   -1.0f + 0.5f * Constants::HEIGHT_UNIT,                            1.0f, 0.0f, //bottom-right
            // clang-format on
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::DrawDisplayElement(GameInformation &gameInformation) {
    for (DisplayBlock *d : gameInformation.displayBlocks) {
        this->drawSprite(d->sprite, d->position, d->size);
    }
}

void SpriteRenderer::updateView(float dt) {
    this->pengoAnimator->animate(dt);

    this->bottomWallAnimator->animate(dt);
    this->topWallAnimator->animate(dt);
    this->leftWallAnimator->animate(dt);
    this->rightWallAnimator->animate(dt);

    for (BlockAnimator *ba : this->blockAnimators)
        ba->animate(dt);
    for (EnemyAnimator *ea : this->enemyAnimators)
        ea->animate(dt);
}

void SpriteRenderer::initDisplayInformation() {
    this->P1 = GameInformation({(-0.5f * Constants::WIDTH_UNIT + 0.5f * Constants::WIDTH_UNIT),
                                -0.5f * Constants::HEIGHT_UNIT + 17 * Constants::HEIGHT_UNIT},
                               {0.5f, 0.5f, (0.5f * (-1 + 0.5f * Constants::WIDTH_UNIT)) + 0.5f * Constants::WIDTH_UNIT,
                                (0.5f * (-1 + 0.5f * Constants::HEIGHT_UNIT)) + 0.5f * Constants::HEIGHT_UNIT},
                               2);
    this->Score =
            GameInformation({(-0.5f * Constants::WIDTH_UNIT + 4.5f * Constants::WIDTH_UNIT),
                             -0.5f * Constants::HEIGHT_UNIT + 17 * Constants::HEIGHT_UNIT},
                            {0.5f, 0.5f, (0.5f * (-1 + 0.5f * Constants::WIDTH_UNIT)) + 0.5f * Constants::WIDTH_UNIT,
                             (0.5f * (-1 + 0.5f * Constants::HEIGHT_UNIT)) + 0.5f * Constants::HEIGHT_UNIT},
                            6);
}

void SpriteRenderer::loadSprites() {
    // load textures
    // Load all Iceblock Textures
    ResourceManager::loadTexture("../Game2D/res/sprites/Iceblock.bmp", "iceblock");
    ResourceManager::loadTexture("../Game2D/res/sprites/IceblockGreen.bmp", "iceblockGreen");
    ResourceManager::loadTexture("../Game2D/res/sprites/IceblockBreaking0.bmp", "iceblockBreaking0");
    ResourceManager::loadTexture("../Game2D/res/sprites/IceblockBreaking1.bmp", "iceblockBreaking1");
    ResourceManager::loadTexture("../Game2D/res/sprites/IceblockBreaking2.bmp", "iceblockBreaking2");
    ResourceManager::loadTexture("../Game2D/res/sprites/IceblockBreaking3.bmp", "iceblockBreaking3");

    // Load Diamondblock Textures
    ResourceManager::loadTexture("../Game2D/res/sprites/Diamondblock.bmp", "diamondblock");

    // Load Wall Textures
    ResourceManager::loadTexture("../Game2D/res/sprites/Wall_LR.bmp", "wallLR");
    ResourceManager::loadTexture("../Game2D/res/sprites/Wall_LR_00.bmp", "wallLR_00");
    ResourceManager::loadTexture("../Game2D/res/sprites/Wall_LR_01.bmp", "wallLR_01");
    ResourceManager::loadTexture("../Game2D/res/sprites/Wall_BT.bmp", "wallBT");
    ResourceManager::loadTexture("../Game2D/res/sprites/Wall_BT_00.bmp", "wallBT_00");
    ResourceManager::loadTexture("../Game2D/res/sprites/Wall_BT_01.bmp", "wallBT_01");

    // Load all Pengo Textures
    ResourceManager::loadTexture("../Game2D/res/sprites/PengoRight.bmp", "pengoRight");
    ResourceManager::loadTexture("../Game2D/res/sprites/PengoLeft.bmp", "pengoLeft");
    ResourceManager::loadTexture("../Game2D/res/sprites/PengoMoveRight.bmp", "pengoMoveRight");
    ResourceManager::loadTexture("../Game2D/res/sprites/PengoMoveLeft.bmp", "pengoMoveLeft");
    ResourceManager::loadTexture("../Game2D/res/sprites/PengoDown.bmp", "pengoDown");
    ResourceManager::loadTexture("../Game2D/res/sprites/PengoMoveDown.bmp", "pengoMoveDown");
    ResourceManager::loadTexture("../Game2D/res/sprites/PengoUp.bmp", "pengoUp");
    ResourceManager::loadTexture("../Game2D/res/sprites/PengoMoveUp.bmp", "pengoMoveUp");
    ResourceManager::loadTexture("../Game2D/res/sprites/PengoPushRight.bmp", "pengoPushRight");
    ResourceManager::loadTexture("../Game2D/res/sprites/PengoPushLeft.bmp", "pengoPushLeft");
    ResourceManager::loadTexture("../Game2D/res/sprites/PengoPostPushUp.bmp", "pengoPostPushUp");
    ResourceManager::loadTexture("../Game2D/res/sprites/PengoPushUp.bmp", "pengoPushUp");
    ResourceManager::loadTexture("../Game2D/res/sprites/PengoPostPushDown.bmp", "pengoPostPushDown");
    ResourceManager::loadTexture("../Game2D/res/sprites/PengoPushDown.bmp", "pengoPushDown");
    ResourceManager::loadTexture("../Game2D/res/sprites/PengoPostPushLeft.bmp", "pengoPostPushLeft");
    ResourceManager::loadTexture("../Game2D/res/sprites/PengoPostPushRight.bmp", "pengoPostPushRight");

    // Load all Wandering Enemy Textures
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemyMoveRight00.bmp", "enemyMoveRight00");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemyMoveLeft00.bmp", "enemyMoveLeft00");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemyMoveDown00.bmp", "enemyMoveDown00");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemyMoveUp00.bmp", "enemyMoveUp00");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemyMoveRight01.bmp", "enemyMoveRight01");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemyMoveLeft01.bmp", "enemyMoveLeft01");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemyMoveDown01.bmp", "enemyMoveDown01");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemyMoveUp01.bmp", "enemyMoveUp01");
    // Load all Boxing Enemy Textures
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemyBoxerRight00.bmp", "enemyBoxerRight00");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemyBoxerLeft00.bmp", "enemyBoxerLeft00");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemyBoxerDown00.bmp", "enemyBoxerDown00");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemyBoxerUp00.bmp", "enemyBoxerUp00");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemyBoxerRight01.bmp", "enemyBoxerRight01");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemyBoxerLeft01.bmp", "enemyBoxerLeft01");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemyBoxerDown01.bmp", "enemyBoxerDown01");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemyBoxerUp01.bmp", "enemyBoxerUp01");
    // Load Stunned Enemy Texture
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemyStunnedRight.bmp", "enemyStunnedRight");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemyStunnedLeft.bmp", "enemyStunnedLeft");
    // Load Spawning Enemy Textures
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemySpawn0.bmp", "enemySpawn0");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemySpawn1.bmp", "enemySpawn1");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemySpawn2.bmp", "enemySpawn2");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemySpawn3.bmp", "enemySpawn3");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemySpawn4.bmp", "enemySpawn4");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemySpawn5.bmp", "enemySpawn5");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemySpawn6.bmp", "enemySpawn6");
    ResourceManager::loadTexture("../Game2D/res/sprites/EnemySpawn7.bmp", "enemySpawn7");

    ResourceManager::loadTexture("../Game2D/res/sprites/Placeholder.bmp", "placeholder");
    ResourceManager::loadTexture("../Game2D/res/sprites/One.bmp", "One");
    ResourceManager::loadTexture("../Game2D/res/sprites/P.bmp", "P");
    ResourceManager::loadTexture("../Game2D/res/sprites/0.bmp", "0");
    ResourceManager::loadTexture("../Game2D/res/sprites/1.bmp", "1");
    ResourceManager::loadTexture("../Game2D/res/sprites/2.bmp", "2");
    ResourceManager::loadTexture("../Game2D/res/sprites/3.bmp", "3");
    ResourceManager::loadTexture("../Game2D/res/sprites/4.bmp", "4");
    ResourceManager::loadTexture("../Game2D/res/sprites/5.bmp", "5");
    ResourceManager::loadTexture("../Game2D/res/sprites/6.bmp", "6");
    ResourceManager::loadTexture("../Game2D/res/sprites/7.bmp", "7");
    ResourceManager::loadTexture("../Game2D/res/sprites/8.bmp", "8");
    ResourceManager::loadTexture("../Game2D/res/sprites/9.bmp", "9");
}

void SpriteRenderer::initLevelView(GameLevel *gameLevel) {
    // initialize pengo view
    this->pengoAnimator = new PengoAnimator(&gameLevel->Pengo, 0.5f, 0.25f, ResourceManager::getTexture("pengoRight"));

    // initialize block views
    for (Block &b : gameLevel->Blocks) {
        if (!b.isUnbreakable) {
            this->blockAnimators.push_back(new BlockAnimator(&b, 3.0f, 0.5f, ResourceManager::getTexture("iceblock")));
        } else if (b.isUnbreakable) {
            this->blockAnimators.push_back(
                    new BlockAnimator(&b, 3.0f, 0.5f, ResourceManager::getTexture("diamondblock")));
        }
    }

    // initialize wall views
    this->bottomWallAnimator = new WallAnimator(&gameLevel->BottomWall, 0.5f);
    this->topWallAnimator = new WallAnimator(&gameLevel->TopWall, 0.5f);
    this->leftWallAnimator = new WallAnimator(&gameLevel->LeftWall, 0.5f);
    this->rightWallAnimator = new WallAnimator(&gameLevel->RightWall, 0.5f);

    // initialize enemy views
    for (std::shared_ptr<Enemy> &e : gameLevel->Enemies) {
        this->enemyAnimators.push_back(new EnemyAnimator(e, 0.4f, 3.0f, 1.5f));
    }
}

void SpriteRenderer::update(GameLevel *gameLevel) {
    std::shared_ptr<Enemy> enemy = nullptr;
    // Check if an enemy was killed (= if there exists an animator for whose enemy does not exist anymore)
    for (EnemyAnimator *ea : this->enemyAnimators) {
        if (std::find(gameLevel->Enemies.begin(), gameLevel->Enemies.end(), ea->enemy) != gameLevel->Enemies.end()) {
            continue;
        } else {
            enemy = ea->enemy;
            break;
        }
    }
    if (enemy != nullptr) {
        removeAnimatorOfKilledEnemy(enemy);
        return;
    }

    // Check if an enemy was spawned (= if there exists an enemy with no animator)
    bool animatorExists = false;
    for (std::shared_ptr<Enemy> &e : gameLevel->Enemies) {
        for (EnemyAnimator *ea : this->enemyAnimators) {
            if (ea->enemy->id == e->id) {
                animatorExists = true;
            }
        }
        if (!animatorExists) {
            enemy = e;
            break;
        } else {
            animatorExists = false;
        }
    }

    if (enemy != nullptr) {
        createAnimatorForSpawnedEnemy(enemy);
    }
}

void SpriteRenderer::removeAnimatorOfKilledEnemy(std::shared_ptr<Enemy> &enemy) {
    this->enemyAnimators.erase(std::remove_if(this->enemyAnimators.begin(), this->enemyAnimators.end(),
                                              [&](EnemyAnimator *ea) { return ea->enemy == enemy; }));
}

void SpriteRenderer::createAnimatorForSpawnedEnemy(std::shared_ptr<Enemy> &enemy) {
    this->enemyAnimators.push_back(new EnemyAnimator(enemy, 0.4f, 3.0f, 1.5f));
}
