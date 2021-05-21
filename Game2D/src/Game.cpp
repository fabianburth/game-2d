#include "Game.h"
#include "ResourceManager.h"
#include <array>

#include <iostream>
// Game-related State data

Game::Game(unsigned int width, unsigned int height)
	: PengoState(GameState::GAME_ACTIVE), Keys(), Width(width), Height(height) { }

Game::~Game()
{
	//delete Pengo;
	//delete Renderer;
	//delete pengoAnimator;
	//delete blockAnimator;
}

void Game::Init()
{
	// load shaders
	ResourceManager::LoadShader("res/shaders/sprites.vs", "res/shaders/sprites.fs", "sprite");
	// configure shaders
	ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
	// set render-specific controls
	Shader shader = ResourceManager::GetShader("sprite");
	this->Renderer = new SpriteRenderer(shader);
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
	ResourceManager::LoadTexture("res/sprites/Wall_LR_00.bmp", "wallLR_00");
	ResourceManager::LoadTexture("res/sprites/Wall_LR_01.bmp", "wallLR_01");
	ResourceManager::LoadTexture("res/sprites/Wall_BT.bmp", "wallBT");
	ResourceManager::LoadTexture("res/sprites/Wall_BT_00.bmp", "wallBT_00");
	ResourceManager::LoadTexture("res/sprites/Wall_BT_01.bmp", "wallBT_01");

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
	//this->Pengo = one.Pengo;
	this->Levels.push_back(one);
	this->Level = 0;
	this->Pengo = &this->Levels[this->Level].Pengo;

	this->pengoAnimator = new PengoAnimator(&this->Levels[this->Level].Pengo, 0.5f, 0.25f);
	this->blockAnimator = new BlockAnimator(0.5f, &this->Levels[this->Level].Bricks);
	this->wallAnimator = new WallAnimator(&this->Levels[this->Level].BottomWall, &this->Levels[this->Level].TopWall, &this->Levels[this->Level].LeftWall, &this->Levels[this->Level].RightWall, 0.5f);
	//this->Pengo->registerObserver(pengoAnimator);

	//for (Block& tile : this->Levels[this->Level].Bricks)
	//	tile.registerObserver(blockAnimator);
}

void Game::Update(float dt)
{
	// Update Players actual position
	for (Block& block : this->Levels[this->Level].Bricks)
	{
		if (block.position != block.positionToMoveTo)
			block.move(dt);
	}
	this->Pengo->move(dt);
	pengoAnimator->animate(dt);
	blockAnimator->animate(dt);
	wallAnimator->animate(dt);
}

void Game::ProcessInput(float dt)
{
	if (this->PengoState == GameState::GAME_ACTIVE)
	{
		if (Pengo->ready)
		{
			if (this->Keys[GLFW_KEY_LEFT_CONTROL])
			{
				/*if (doCollision(*P, P->direction))
				{
					P->setState(PengoState::PUSH);
				}
				return;*/
				if (checkCollisions(*Pengo, Pengo->direction))
				{
					Block* block = getCollisionBlock(*Pengo, Pengo->direction);
					// Behavior if the collision is with an adjacent block
					if (block != nullptr)
					{
						// Behavior if there actually is a block directly behind the adjacent one
						if (checkCollisions(*block, Pengo->direction))
						{
							// Pengo always tries to break it (Pengo Animation)
							Pengo->setState(PengoState::BREAK);
							// Block only breaks if it's not solid (= not a diamond block)
							if (!block->isUnbreakable)
							{
								block->setState(BlockState::BREAKING);
								return;
							}
							return;
						}
						// Behavior if there is no block directly behind the adjacent one
						else
						{
							Pengo->setState(PengoState::PUSH);
							block->push(Pengo->direction, calculateStepRange(*block, Pengo->direction));
							return;
						}
					}
					// Behavior if the collision is with a wall
					else //if(checkWallCollision(*P, P->direction))
					{
						Pengo->setState(PengoState::BREAK);

						if(Pengo->direction == Direction::UP)
							this->Levels[this->Level].BottomWall.setState(WallState::WOBBLY);
						else if(Pengo->direction == Direction::DOWN)
							this->Levels[this->Level].TopWall.setState(WallState::WOBBLY);
						else if(Pengo->direction == Direction::LEFT)
							this->Levels[this->Level].LeftWall.setState(WallState::WOBBLY);
						else if(Pengo->direction == Direction::RIGHT)
							this->Levels[this->Level].RightWall.setState(WallState::WOBBLY);

						return;
					}
				}
			}
			if (this->Keys[GLFW_KEY_D])
			{
				Pengo->setDirection(Direction::RIGHT);
				Pengo->setState(PengoState::WALK);
				if (!checkCollisions(*Pengo, Direction::RIGHT))
				{
					Pengo->setPositionToMoveTo();
				}
				return;
			}
			if (this->Keys[GLFW_KEY_A])
			{
				Pengo->setDirection(Direction::LEFT);
				Pengo->setState(PengoState::WALK);
				if (!checkCollisions(*Pengo, Direction::LEFT))
				{
					Pengo->setPositionToMoveTo();
				}
				return;
			}
			if (this->Keys[GLFW_KEY_W])
			{
				Pengo->setDirection(Direction::UP);
				Pengo->setState(PengoState::WALK);
				if (!checkCollisions(*Pengo, Direction::UP))
				{
					Pengo->setPositionToMoveTo();
				}
				return;
			}
			if (this->Keys[GLFW_KEY_S])
			{
				Pengo->setDirection(Direction::DOWN);
				Pengo->setState(PengoState::WALK);
				if (!checkCollisions(*Pengo, Direction::DOWN))
				{
					Pengo->setPositionToMoveTo();
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
		//this->Levels[this->Level].Draw(*Renderer);
		this->Renderer->DrawLevel(this->Levels[this->Level]);
	}

	// Texture2D texture = ResourceManager::GetTexture("pengo");
	// Renderer->DrawSprite(texture, { 6.0f * Constants::WIDTH_UNIT, 8.0f * Constants::HEIGHT_UNIT });
}

bool Game::checkCollisions(GameObject& gameObject, Direction d)
{
	for (Block& block : this->Levels[this->Level].Bricks)
	{
		if (block.state != BlockState::BROKEN)
		{
			if (checkBlockCollision(gameObject, block, d) || checkWallCollision(gameObject, d))
			{
				return true;
			}
		}
	}
	return false;
}

//bool Game::doCollision(GameObject& gameObject, Direction d)
//{
//	for (Block& block : this->Levels[this->Level].Bricks)
//	{
//		if (block.state != BlockState::BROKEN)
//		{
//			if (checkBlockCollision(gameObject, block, d))
//			{
//				if (checkCollisions(block, d) && !block.IsUnbreakable)
//				{
//					block.destroy();
//				}
//				else
//				{
//					block.yeet(d, calculateStepRange(block, d));
//				}
//				return true;
//			}
//			else
//				if (checkWallCollision(gameObject, d))
//				{
//					return true;
//				}
//		}
//	}
//	return false;
//}

Block* Game::getCollisionBlock(GameObject& gameObject, Direction d)
{
	for (Block& block : this->Levels[this->Level].Bricks)
	{
		if (block.state != BlockState::BROKEN)
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
		collisionX = ((one.position[0] + 2 * Constants::WIDTH_UNIT) - two.position[0]) > EPSILON && ((two.position[0] + Constants::WIDTH_UNIT) - (one.position[0] + Constants::WIDTH_UNIT)) > EPSILON;
		collisionY = ((one.position[1] + Constants::HEIGHT_UNIT) - two.position[1]) > EPSILON && ((two.position[1] + Constants::HEIGHT_UNIT) - one.position[1]) > EPSILON;
		break;
	case Direction::LEFT:
		collisionX = ((one.position[0] + Constants::WIDTH_UNIT - Constants::WIDTH_UNIT) - two.position[0]) > EPSILON && ((two.position[0] + Constants::WIDTH_UNIT) - (one.position[0] - Constants::WIDTH_UNIT)) > EPSILON;
		collisionY = ((one.position[1] + Constants::HEIGHT_UNIT) - two.position[1]) > EPSILON && ((two.position[1] + Constants::HEIGHT_UNIT) - one.position[1]) > EPSILON;
		break;
	case Direction::UP:
		collisionX = ((one.position[0] + Constants::WIDTH_UNIT) - two.position[0]) > EPSILON && ((two.position[0] + Constants::WIDTH_UNIT) - one.position[0]) > EPSILON;
		collisionY = ((one.position[1] + 2 * Constants::HEIGHT_UNIT) - two.position[1]) > EPSILON && ((two.position[1] + Constants::HEIGHT_UNIT) - (one.position[1] + Constants::HEIGHT_UNIT)) > EPSILON;
		break;
	case Direction::DOWN:
		collisionX = ((one.position[0] + Constants::WIDTH_UNIT) - two.position[0]) > EPSILON && ((two.position[0] + Constants::WIDTH_UNIT) - one.position[0]) > EPSILON;
		collisionY = ((one.position[1] + Constants::HEIGHT_UNIT - Constants::HEIGHT_UNIT) - two.position[1]) > EPSILON && ((two.position[1] + Constants::HEIGHT_UNIT) - (one.position[1] - Constants::HEIGHT_UNIT)) > EPSILON;
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
		collision = !((-1.0f + 0.5f * Constants::WIDTH_UNIT) + one.position[0] + Constants::WIDTH_UNIT < 1.0f - 0.5f * Constants::WIDTH_UNIT);
		break;
	case Direction::LEFT:
		collision = !((-1.0f + 0.5f * Constants::WIDTH_UNIT) + one.position[0] - Constants::WIDTH_UNIT >= -1.0f + 0.5f * Constants::WIDTH_UNIT);
		break;
	case Direction::UP:
		collision = !((-1.0f + 0.5f * Constants::HEIGHT_UNIT) + one.position[1] + Constants::HEIGHT_UNIT < 1.0f - 2 * Constants::HEIGHT_UNIT - 0.5f * Constants::HEIGHT_UNIT);	
		break;
	case Direction::DOWN:
		collision = !((-1.0f + 0.5f * Constants::HEIGHT_UNIT) + one.position[1] - Constants::HEIGHT_UNIT >= -1.0f + 0.5f * Constants::HEIGHT_UNIT);
		break;
	}
	return collision;
}

int Game::calculateStepRange(Block& block, Direction d)
{
	int stepWidth = 0;
	std::array<float, 2> originalPosition = block.position;

	while (!checkCollisions(block, d))
	{
		block.setPositionToMoveTo(d);
		block.position = block.positionToMoveTo;
		stepWidth++;
	}

	block.position = originalPosition;
	return stepWidth;

}


