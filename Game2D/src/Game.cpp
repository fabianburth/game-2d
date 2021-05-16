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
GameObject* movingBlock;
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
	delete movingBlock;
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
	ResourceManager::LoadTexture("res/sprites/PengoPostPushUp.bmp", "pengoPostPushUp");
	ResourceManager::LoadTexture("res/sprites/PengoPushUp.bmp", "pengoPushUp");
	ResourceManager::LoadTexture("res/sprites/PengoPostPushDown.bmp", "pengoPostPushDown");
	ResourceManager::LoadTexture("res/sprites/PengoPushDown.bmp", "pengoPushDown");
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
	for (GameObject& block : this->Levels[this->Level].Bricks)
	{
		if (block.Position != block.newPosition)
			block.move({ WIDTH_UNIT * dt * 12, HEIGHT_UNIT * dt * 12 });
	}
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
				/*if (doCollision(*P, P->direction))
				{
					P->setState(PengoState::PUSH);
				}
				return;*/
				if (checkCollisions(*P, P->direction))
				{
					GameObject* block = getCollisionBlock(*P, P->direction);
					// Behavior if the collision is with an adjacent block
					if (block != nullptr)
					{
						// Behavior if there actually is a block directly behind the adjacent one
						if (checkCollisions(*block, P->direction))
						{
							// Pengo always tries to break it (Pengo Animation)
							P->setState(PengoState::BREAK);
							// Block only breaks if it's not solid (= not a diamond block)
							if (!block->IsSolid)
							{
								block->destroy();
								return;
							}
						}
						// Behavior if there is no block directly behind the adjacent one
						else
						{
							P->setState(PengoState::PUSH);
							block->yeet(P->direction, calculateStepRange(*block, P->direction));
							return;
						}
					}
					// Behavior if the collision is with a wall
					else //if(checkWallCollision(*P, P->direction))
					{
						P->setState(PengoState::BREAK);
						return;
					}
				}
			}
			if (this->Keys[GLFW_KEY_D])
			{
				P->setDirection(Direction::RIGHT);
				P->setState(PengoState::WALK);
				if (!checkCollisions(*P, Direction::RIGHT))
				{
					P->calculateMovement();
				}
				return;
			}
			if (this->Keys[GLFW_KEY_A])
			{
				P->setDirection(Direction::LEFT);
				P->setState(PengoState::WALK);
				if (!checkCollisions(*P, Direction::LEFT))
				{
					P->calculateMovement();
				}
				return;
			}
			if (this->Keys[GLFW_KEY_W])
			{
				P->setDirection(Direction::UP);
				P->setState(PengoState::WALK);
				if (!checkCollisions(*P, Direction::UP))
				{
					P->calculateMovement();
				}
				return;
			}
			if (this->Keys[GLFW_KEY_S])
			{
				P->setDirection(Direction::DOWN);
				P->setState(PengoState::WALK);
				if (!checkCollisions(*P, Direction::DOWN))
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

bool Game::checkCollisions(GameObject& gameObject, Direction d)
{
	for (GameObject& block : this->Levels[this->Level].Bricks)
	{
		if (!block.Destroyed)
		{
			if (checkBlockCollision(gameObject, block, d) || checkWallCollision(gameObject, d))
			{
				return true;
			}
		}
	}
	return false;
}

bool Game::doCollision(GameObject& gameObject, Direction d)
{
	for (GameObject& block : this->Levels[this->Level].Bricks)
	{
		if (!block.Destroyed)
		{
			if (checkBlockCollision(gameObject, block, d))
			{
				if (checkCollisions(block, d) && !block.IsSolid)
				{
					block.destroy();
				}
				else
				{
					block.yeet(d, calculateStepRange(block, d));
				}
				return true;
			}
			else
				if (checkWallCollision(gameObject, d))
				{
					return true;
				}
		}
	}
	return false;
}

GameObject* Game::getCollisionBlock(GameObject& gameObject, Direction d)
{
	for (GameObject& block : this->Levels[this->Level].Bricks)
	{
		if (!block.Destroyed)
		{
			if (checkBlockCollision(gameObject, block, d))
			{
				return &block;
			}
		}
	}
	return nullptr;
}

bool Game::checkBlockCollision(GameObject& one, GameObject& two, Direction d)
{
	bool collisionX = false;
	bool collisionY = false;

	switch (d)
	{
	case Direction::RIGHT:
		collisionX = ((one.Position[0] + 2 * WIDTH_UNIT) - two.Position[0]) > EPSILON && ((two.Position[0] + WIDTH_UNIT) - (one.Position[0] + WIDTH_UNIT)) > EPSILON;
		collisionY = ((one.Position[1] + HEIGHT_UNIT) - two.Position[1]) > EPSILON && ((two.Position[1] + HEIGHT_UNIT) - one.Position[1]) > EPSILON;
		break;
	case Direction::LEFT:
		collisionX = ((one.Position[0] + WIDTH_UNIT - WIDTH_UNIT) - two.Position[0]) > EPSILON && ((two.Position[0] + WIDTH_UNIT) - (one.Position[0] - WIDTH_UNIT)) > EPSILON;
		collisionY = ((one.Position[1] + HEIGHT_UNIT) - two.Position[1]) > EPSILON && ((two.Position[1] + HEIGHT_UNIT) - one.Position[1]) > EPSILON;
		break;
	case Direction::UP:
		collisionX = ((one.Position[0] + WIDTH_UNIT) - two.Position[0]) > EPSILON && ((two.Position[0] + WIDTH_UNIT) - one.Position[0]) > EPSILON;
		collisionY = ((one.Position[1] + 2 * HEIGHT_UNIT) - two.Position[1]) > EPSILON && ((two.Position[1] + HEIGHT_UNIT) - (one.Position[1] + HEIGHT_UNIT)) > EPSILON;
		break;
	case Direction::DOWN:
		collisionX = ((one.Position[0] + WIDTH_UNIT) - two.Position[0]) > EPSILON && ((two.Position[0] + WIDTH_UNIT) - one.Position[0]) > EPSILON;
		collisionY = ((one.Position[1] + HEIGHT_UNIT - HEIGHT_UNIT) - two.Position[1]) > EPSILON && ((two.Position[1] + HEIGHT_UNIT) - (one.Position[1] - HEIGHT_UNIT)) > EPSILON;
		break;
	}
	return collisionX && collisionY;
}


bool Game::checkWallCollision(GameObject& one, Direction d)
{
	bool collision = false;

	switch (d)
	{
	case Direction::RIGHT:
		collision = !((-1.0f + 0.5f * WIDTH_UNIT) + one.Position[0] + WIDTH_UNIT < 1.0f - 0.5f * WIDTH_UNIT);
		break;
	case Direction::LEFT:
		collision = !((-1.0f + 0.5f * WIDTH_UNIT) + one.Position[0] - WIDTH_UNIT >= -1.0f + 0.5f * WIDTH_UNIT);
		break;
	case Direction::UP:
		collision = !((-1.0f + 0.5f * HEIGHT_UNIT) + one.Position[1] + HEIGHT_UNIT < 1.0f - 2 * HEIGHT_UNIT - 0.5f * HEIGHT_UNIT);	
		break;
	case Direction::DOWN:
		collision = !((-1.0f + 0.5f * HEIGHT_UNIT) + one.Position[1] - HEIGHT_UNIT >= -1.0f + 0.5f * HEIGHT_UNIT);
		break;
	}
	return collision;
}

int Game::calculateStepRange(GameObject& block, Direction d)
{
	int stepWidth = 0;
	std::array<float, 2> originalPosition = block.Position;

	while (!checkCollisions(block, d))
	{
		block.calculateMovement(d);
		block.Position = block.newPosition;
		stepWidth++;
	}

	block.Position = originalPosition;
	return stepWidth;

}


