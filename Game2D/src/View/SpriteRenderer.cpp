#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Shader& shader)
{
    this->shader = shader;
    this->initRenderData();
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
    for (GameObject& wall : gameLevel.LeftWall.wallComponents)
        this->DrawObject(wall);

    for (GameObject& wall : gameLevel.RightWall.wallComponents)
        this->DrawObject(wall);

    for (GameObject& wall : gameLevel.TopWall.wallComponents)
        this->DrawObject(wall);

    for (GameObject& wall : gameLevel.BottomWall.wallComponents)
        this->DrawObject(wall);

    for (Block& tile : gameLevel.Bricks)
        if (tile.state != BlockState::BROKEN)
            this->DrawObject(tile);

    for (Enemy* enemy : gameLevel.Enemies)
        this->DrawObject(*enemy);

    this->DrawObject(gameLevel.Pengo);
    //this->DrawObject(gameLevel.d);
    this->DrawDisplayElement(gameLevel.P1);
    this->DrawDisplayElement(gameLevel.Score);
}

void SpriteRenderer::initRenderData()
{
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

