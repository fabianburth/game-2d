#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Shader& shader)
{
    this->shader = shader;
    this->initRenderData();

    this->initDisplayInformation();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::DrawSprite(Texture2D& texture, std::array<float, 2> position, std::array<float, 4> size, std::array<float, 3> color)
{
    // prepare transformations
    this->shader.Use();

    // the first 2 elements of size are the scaling values for x and y
    // the other 2 elements are the values to correct the position when scaling
    this->shader.SetVector4f("size", size[0], size[1], size[2], size[3]);
    this->shader.SetVector2f("position", position[0], position[1]);
    // render textured quad
    this->shader.SetVector3f("spriteColor", color[0], color[1], color[2]);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::DrawLevel(GameLevel& gameLevel)
{
    for (GameObject& wall : leftWallAnimator->wall->wallComponents)
        this->DrawSprite(leftWallAnimator->sprite, wall.position, wall.size);

    for (GameObject& wall : rightWallAnimator->wall->wallComponents)
        this->DrawSprite(rightWallAnimator->sprite, wall.position, wall.size);

    for (GameObject& wall : topWallAnimator->wall->wallComponents)
        this->DrawSprite(topWallAnimator->sprite, wall.position, wall.size);

    for (GameObject& wall : bottomWallAnimator->wall->wallComponents)
        this->DrawSprite(bottomWallAnimator->sprite, wall.position, wall.size);

    for (BlockAnimator* blockAnimator : blockAnimators)
        if (blockAnimator->block->state != BlockState::BROKEN)
            this->DrawSprite(blockAnimator->sprite, blockAnimator->block->position, blockAnimator->block->size);

    for (EnemyAnimator* enemyAnimator : enemyAnimators)
        this->DrawSprite(enemyAnimator->sprite, enemyAnimator->enemy->position, enemyAnimator->enemy->size);

    this->DrawSprite(pengoAnimator->sprite, pengoAnimator->pengo->position, pengoAnimator->pengo->size);
    //this->DrawObject(gameLevel.d);
    this->P1.show("1P");
    this->DrawDisplayElement(this->P1);
    this->Score.show(std::to_string(gameLevel.score.score));
    this->DrawDisplayElement(this->Score);
}

void SpriteRenderer::initRenderData()
{
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = {
        // pos                                                                                                                            // tex
        //x                                                             //y
        -1.0f + 0.5f * Constants::WIDTH_UNIT,                           -1.0f + 0.5f * Constants::HEIGHT_UNIT,                            0.0f, 0.0f, //bottom-left
        -1.0f + 0.5f * Constants::WIDTH_UNIT,                           -1.0f + 0.5f * Constants::HEIGHT_UNIT + Constants::HEIGHT_UNIT,   0.0f, 1.0f, //top-left
        -1.0f + 0.5f * Constants::WIDTH_UNIT + Constants::WIDTH_UNIT,   -1.0f + 0.5f * Constants::HEIGHT_UNIT,                            1.0f, 0.0f, //bottom-right

        -1.0f + 0.5f * Constants::WIDTH_UNIT,                           -1.0f + 0.5f * Constants::HEIGHT_UNIT + Constants::HEIGHT_UNIT,   0.0f, 1.0f, //top-left
        -1.0f + 0.5f * Constants::WIDTH_UNIT + Constants::WIDTH_UNIT,   -1.0f + 0.5f * Constants::HEIGHT_UNIT + Constants::HEIGHT_UNIT,   1.0f, 1.0f, //top-right
        -1.0f + 0.5f * Constants::WIDTH_UNIT + Constants::WIDTH_UNIT,   -1.0f + 0.5f * Constants::HEIGHT_UNIT,                            1.0f, 0.0f, //bottom-right
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::DrawObject(GameObject& gameObject)
{
    this->DrawSprite(gameObject.sprite, gameObject.position, gameObject.size);
}

void SpriteRenderer::DrawDisplayElement(GameInformation& gameInformation)
{
    for (DisplayBlock* d : gameInformation.displayBlocks)
    {
        this->DrawSprite(d->sprite, d->position, d->size);
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
    this->P1 = GameInformation({(-0.5f * Constants::WIDTH_UNIT + 0.5f * Constants::WIDTH_UNIT), -0.5f * Constants::HEIGHT_UNIT + 17 * Constants::HEIGHT_UNIT},
                         {0.5f, 0.5f, (0.5f * (-1 + 0.5f * Constants::WIDTH_UNIT)) + 0.5f * Constants::WIDTH_UNIT,
                          (0.5f * (-1 + 0.5f * Constants::HEIGHT_UNIT)) + 0.5f * Constants::HEIGHT_UNIT}, 2);
    //this->P1.show("1P");
    this->Score = GameInformation({(-0.5f * Constants::WIDTH_UNIT + 4.5f * Constants::WIDTH_UNIT), -0.5f * Constants::HEIGHT_UNIT + 17 * Constants::HEIGHT_UNIT},
                            {0.5f, 0.5f, (0.5f * (-1 + 0.5f * Constants::WIDTH_UNIT)) + 0.5f * Constants::WIDTH_UNIT,
                             (0.5f * (-1 + 0.5f * Constants::HEIGHT_UNIT)) + 0.5f * Constants::HEIGHT_UNIT}, 6);
}

void SpriteRenderer::initLevelView(GameLevel* gameLevel) {
    //initialize pengo view
    this->pengoAnimator = new PengoAnimator(&gameLevel->Pengo, 0.5f, 0.25f, ResourceManager::GetTexture("pengoRight"));

    //initialize block views
    for (Block &b : gameLevel->Blocks){
        if(!b.isUnbreakable){
            this->blockAnimators.push_back(new BlockAnimator(&b, 3.0f, 0.5f, ResourceManager::GetTexture("iceblock")));
        } else if(b.isUnbreakable){
            this->blockAnimators.push_back(new BlockAnimator(&b, 3.0f, 0.5f, ResourceManager::GetTexture("diamondblock")));
        }
    }

    //initialize wall views
    this->bottomWallAnimator = new WallAnimator(&gameLevel->BottomWall, 0.5f);
    this->topWallAnimator = new WallAnimator(&gameLevel->TopWall, 0.5f);
    this->leftWallAnimator = new WallAnimator(&gameLevel->LeftWall, 0.5f);
    this->rightWallAnimator = new WallAnimator(&gameLevel->RightWall, 0.5f);

    //initialize enemy views
    for (Enemy *e : gameLevel->Enemies) {
        if(e->baseType == "Move"){
            this->enemyAnimators.push_back(new EnemyAnimator(e, 0.4f, 3.0f, 1.5f, ResourceManager::GetTexture("enemyMove" + stringDirection(Direction::DOWN) + "00")));
        } else if(e->baseType == "Boxer"){
            this->enemyAnimators.push_back(new EnemyAnimator(e, 0.4f, 3.0f, 1.5f, ResourceManager::GetTexture("enemyBoxer" + stringDirection(Direction::DOWN) + "00")));
        }
    }
}

