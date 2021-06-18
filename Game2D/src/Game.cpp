#include "Game.h"
#include "ResourceManager.h"
#include <array>
#include <Windows.h>

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
	ResourceManager::LoadTexture("res/sprites/IceblockGreen.bmp", "iceblockGreen");
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

	// Load all Wandering Enemy Textures
	ResourceManager::LoadTexture("res/sprites/EnemyMoveRight00.bmp", "enemyMoveRight00");
	ResourceManager::LoadTexture("res/sprites/EnemyMoveLeft00.bmp", "enemyMoveLeft00");
	ResourceManager::LoadTexture("res/sprites/EnemyMoveDown00.bmp", "enemyMoveDown00");
	ResourceManager::LoadTexture("res/sprites/EnemyMoveUp00.bmp", "enemyMoveUp00");
	ResourceManager::LoadTexture("res/sprites/EnemyMoveRight01.bmp", "enemyMoveRight01");
	ResourceManager::LoadTexture("res/sprites/EnemyMoveLeft01.bmp", "enemyMoveLeft01");
	ResourceManager::LoadTexture("res/sprites/EnemyMoveDown01.bmp", "enemyMoveDown01");
	ResourceManager::LoadTexture("res/sprites/EnemyMoveUp01.bmp", "enemyMoveUp01");
	// Load all Boxing Enemy Textures
	ResourceManager::LoadTexture("res/sprites/EnemyBoxerRight00.bmp", "enemyBoxerRight00");
	ResourceManager::LoadTexture("res/sprites/EnemyBoxerLeft00.bmp", "enemyBoxerLeft00");
	ResourceManager::LoadTexture("res/sprites/EnemyBoxerDown00.bmp", "enemyBoxerDown00");
	ResourceManager::LoadTexture("res/sprites/EnemyBoxerUp00.bmp", "enemyBoxerUp00");
	ResourceManager::LoadTexture("res/sprites/EnemyBoxerRight01.bmp", "enemyBoxerRight01");
	ResourceManager::LoadTexture("res/sprites/EnemyBoxerLeft01.bmp", "enemyBoxerLeft01");
	ResourceManager::LoadTexture("res/sprites/EnemyBoxerDown01.bmp", "enemyBoxerDown01");
	ResourceManager::LoadTexture("res/sprites/EnemyBoxerUp01.bmp", "enemyBoxerUp01");
	// Load Stunned Enemy Texture
	ResourceManager::LoadTexture("res/sprites/EnemyStunnedRight.bmp", "enemyStunnedRight");
	ResourceManager::LoadTexture("res/sprites/EnemyStunnedLeft.bmp", "enemyStunnedLeft");
	// Load Spawning Enemy Textures
	ResourceManager::LoadTexture("res/sprites/EnemySpawn0.bmp", "enemySpawn0");
	ResourceManager::LoadTexture("res/sprites/EnemySpawn1.bmp", "enemySpawn1");
	ResourceManager::LoadTexture("res/sprites/EnemySpawn2.bmp", "enemySpawn2");
	ResourceManager::LoadTexture("res/sprites/EnemySpawn3.bmp", "enemySpawn3");
	ResourceManager::LoadTexture("res/sprites/EnemySpawn4.bmp", "enemySpawn4");
	ResourceManager::LoadTexture("res/sprites/EnemySpawn5.bmp", "enemySpawn5");
	ResourceManager::LoadTexture("res/sprites/EnemySpawn6.bmp", "enemySpawn6");
	ResourceManager::LoadTexture("res/sprites/EnemySpawn7.bmp", "enemySpawn7");

	ResourceManager::LoadTexture("res/sprites/Placeholder.bmp", "placeholder");
	ResourceManager::LoadTexture("res/sprites/One.bmp", "One");
	ResourceManager::LoadTexture("res/sprites/P.bmp", "P");
	ResourceManager::LoadTexture("res/sprites/0.bmp", "0");
	ResourceManager::LoadTexture("res/sprites/1.bmp", "1");
	ResourceManager::LoadTexture("res/sprites/2.bmp", "2");
	ResourceManager::LoadTexture("res/sprites/3.bmp", "3");
	ResourceManager::LoadTexture("res/sprites/4.bmp", "4");
	ResourceManager::LoadTexture("res/sprites/5.bmp", "5");
	ResourceManager::LoadTexture("res/sprites/6.bmp", "6");
	ResourceManager::LoadTexture("res/sprites/7.bmp", "7");
	ResourceManager::LoadTexture("res/sprites/8.bmp", "8");
	ResourceManager::LoadTexture("res/sprites/9.bmp", "9");


	GameLevel one; one.Load("res/levels/level1.lvl", 448, 576);
	GameLevel two; two.Load("res/levels/level0.lvl", 448, 576);
	//this->Pengo = one.Pengo;
	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Level = 0;
	this->Pengo = &this->Levels[this->Level].Pengo;

	this->pengoAnimator = new PengoAnimator(&this->Levels[this->Level].Pengo, 0.5f, 0.25f);
	for (Block& b : this->Levels[this->Level].Bricks)
		blockAnimators.push_back(new BlockAnimator(0.5f, 3.0f, &b));
	//this->blockAnimator = new BlockAnimator(0.5f, &this->Levels[this->Level].Bricks);
	this->wallAnimator = new WallAnimator(&this->Levels[this->Level].BottomWall, &this->Levels[this->Level].TopWall, &this->Levels[this->Level].LeftWall, &this->Levels[this->Level].RightWall, 0.5f);
	for (Enemy* e : this->Levels[this->Level].Enemies)
	{
		enemyAnimators.push_back(new EnemyAnimator(e, 0.4f, 3.0f, 1.5f));
	}

	for (Block& b : this->Levels[this->Level].Bricks)
	{
		if ((b.state != BlockState::BROKEN && b.state != BlockState::BREAKING) && b.containedEnemy != nullptr)
		{
			b.setState(BlockState::FLASHING);
		}
	}

	for (Enemy* e : this->Levels[this->Level].Enemies)
	{
		e->setState(EnemyState::INITIAL_SPAWNING);
	}


	startClockLevel, startClockEnemyKill = std::clock();

	//this->Pengo->registerObserver(pengoAnimator);

	//for (Block& tile : this->Levels[this->Level].Bricks)
	//	tile.registerObserver(blockAnimator);
}

void Game::Update(float dt)
{
	if (this->PengoState == GameState::GAME_ACTIVE)
	{
		this->Levels[this->Level].Score.show(std::to_string(score));

		if (this->Levels[this->Level].IsCompleted())
		{
			double levelDuration = ((std::clock() - startClockLevel) / (double)CLOCKS_PER_SEC);
			if (levelDuration < 20)
				score += 5000;
			else if (levelDuration < 30)
				score += 2000;
			else if (levelDuration < 40)
				score += 1000;
			else if (levelDuration < 50)
				score += 500;
			else if (levelDuration < 60)
				score += 10;
			else
				score += 0;

			if (this->Level < this->Levels.size())
			{
				initNextLevel();
				return;
			}
		}
		if (!this->Levels[this->Level].diamondBlocksAligned && checkThreeDiamonds())
		{
			this->Levels[this->Level].diamondBlocksAligned = true;
		}

		if (!boxerExists())
		{
			trySettingBoxer();
		}

		if (((std::clock() - startClockEnemyKill) / (double)CLOCKS_PER_SEC) > 60)
			trySettingBoxer();
		// bots do stuff
		for (Enemy* enemy : this->Levels[this->Level].Enemies)
		{
			// if enemies touch a wall that is wobbly, the enemies shall be stunned
			if (this->Levels[this->Level].RightWall.state == WallState::WOBBLY && checkWallCollision(*enemy, Direction::RIGHT)
				|| this->Levels[this->Level].LeftWall.state == WallState::WOBBLY && checkWallCollision(*enemy, Direction::LEFT)
				|| this->Levels[this->Level].TopWall.state == WallState::WOBBLY && checkWallCollision(*enemy, Direction::UP)
				|| this->Levels[this->Level].BottomWall.state == WallState::WOBBLY && checkWallCollision(*enemy, Direction::DOWN))
			{
				enemy->setState(EnemyState::STUNNED);
			}

			// Behavior if enemies touch Pengo
			if (checkCollisionPrecise(*enemy, *Pengo))
			{
				// if enemies touch pengo while they are not stunned, pengo dies
				if (enemy->state != EnemyState::STUNNED)
				{
					enemy->setState(EnemyState::BREAKING);
					std::cout << "GAME OVER" << std::endl;
					PengoState = GameState::GAME_MENU;
				}
				// if enemies touch pengo while they are stunned, the enemy dies
				else
				{
					killEnemy(enemy);
					score += 100;
					if (!this->Levels[this->Level].frozenEnemies.empty())
						spawnEnemy();
				}
			}

			if (enemy->ready == true)
			{
				std::vector<Direction> directions = getInitialDirections(*enemy);

				// Determine a direction with certain propabilities
				//bool movementImpossible = true;
				//while (movementImpossible)
				//{
				std::vector<int> chances = getPropabilityArray(*enemy, directions);
				int index = getDirectionIndex(chances);
				// cover the case when there is no direction to go to
				// for example, if you pushed a block and it happens to be currently flying by the only direction this enemy could go to
				// or you trap the enemy 
				if (directions.empty())
					continue;

				Direction direction = directions.at(index);

				//if (!checkCollisions(enemy, direction))
				//	movementImpossible = false;
				//else
				//	directions.erase(directions.begin() + index);
			//}
				enemy->setDirection(direction);
				if (enemy->state == EnemyState::CHASING)
				{
					Block* block = getCollisionBlock(*enemy, direction);
					if (block != nullptr)
					{
						block->setState(BlockState::BREAKING);
						enemy->setState(EnemyState::BREAKING);
					}
					else
					{
						enemy->setPositionToMoveTo();
					}
				}
				else
				{
					enemy->setPositionToMoveTo();
				}
			}
			enemy->move(dt);
		}

		for (Block& block : this->Levels[this->Level].Bricks)
		{
			if (block.position != block.positionToMoveTo)
			{
				for (Enemy* e : this->Levels[this->Level].Enemies)
				{
					if (checkCollisionPrecise(*e, block))
					{
						killEnemy(e);
						switch (block.killedWithOneMove)
						{
						case 0:
							score += 400;
							break;
						case 1:
							score += 1200;
							break;
						case 2:
							score += 1600;
							break;
						default:
							break;
						}
						++block.killedWithOneMove;

						if (!this->Levels[this->Level].frozenEnemies.empty())
							spawnEnemy();
					}
				}
				block.move(dt);
			}
		}
		this->Pengo->move(dt);
		pengoAnimator->animate(dt);
		wallAnimator->animate(dt);
		for (BlockAnimator* ba : blockAnimators)
			ba->animate(dt);
		for (EnemyAnimator* ea : this->enemyAnimators)
			ea->animate(dt);
	}
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
								if (block->containedEnemy == nullptr)
									score += 30;
								else
									score += 500;
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

						if (Pengo->direction == Direction::UP)
						{
							this->Levels[this->Level].TopWall.setState(WallState::WOBBLY);
						}
						else if (Pengo->direction == Direction::DOWN)
						{
							this->Levels[this->Level].BottomWall.setState(WallState::WOBBLY);
						}
						else if (Pengo->direction == Direction::LEFT)
						{
							this->Levels[this->Level].LeftWall.setState(WallState::WOBBLY);
						}
						else if (Pengo->direction == Direction::RIGHT)
						{
							this->Levels[this->Level].RightWall.setState(WallState::WOBBLY);
						}
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
	//if (this->PengoState == GameState::GAME_ACTIVE)
	//{
		// draw level
		//this->Levels[this->Level].Draw(*Renderer);
	if (this->Levels.size() > this->Level)
		this->Renderer->DrawLevel(this->Levels[this->Level]);
	//}

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
		//collision = !((-1.0f + 0.5f * Constants::WIDTH_UNIT) + one.position[0] + Constants::WIDTH_UNIT < 1.0f - 0.5f * Constants::WIDTH_UNIT );
		collision = !(((one.position[0] + Constants::WIDTH_UNIT) - (12 * Constants::WIDTH_UNIT)) < EPSILON);
		break;
	case Direction::LEFT:
		//collision = !((-1.0f + 0.5f * Constants::WIDTH_UNIT) + one.position[0] - Constants::WIDTH_UNIT >= -1.0f + 0.5f * Constants::WIDTH_UNIT);
		collision = !(0 - (one.position[0] - Constants::WIDTH_UNIT) < EPSILON);
		break;
	case Direction::UP:
		//collision = !((-1.0f + 0.5f * Constants::HEIGHT_UNIT) + one.position[1] + Constants::HEIGHT_UNIT < 1.0f - 2 * Constants::HEIGHT_UNIT - 0.5f * Constants::HEIGHT_UNIT);
		collision = !(((one.position[1] + Constants::HEIGHT_UNIT) - (14 * Constants::HEIGHT_UNIT)) < EPSILON);
		break;
	case Direction::DOWN:
		//collision = !((-1.0f + 0.5f * Constants::HEIGHT_UNIT) + one.position[1] - Constants::HEIGHT_UNIT >= (-1.0f + 0.5f * Constants::HEIGHT_UNIT));
		collision = !(0 - (one.position[1] - Constants::HEIGHT_UNIT) < EPSILON);
		break;
	}
	return collision;
}

bool Game::checkCollisionPrecise(GameObject& one, GameObject& two)
{
	bool collisionX = one.position[0] + Constants::WIDTH_UNIT - two.position[0] > EPSILON && two.position[0] + Constants::WIDTH_UNIT - one.position[0] > EPSILON;
	bool collisionY = one.position[1] + Constants::HEIGHT_UNIT - two.position[1] > EPSILON && two.position[1] + Constants::HEIGHT_UNIT - one.position[1] > EPSILON;
	return collisionX && collisionY;
}

std::vector<int> Game::getPropabilityArray(Enemy& enemy, std::vector<Direction> directions)
{
	std::vector<int> propabilities;
	bool currentDirectionPossible;
	bool oppositeDirectionPossible;
	switch (directions.size())
	{
	case 4:
		propabilities.push_back(90);
		propabilities.push_back(94);
		propabilities.push_back(98);
		propabilities.push_back(100);
		break;
	case 3:
		currentDirectionPossible = std::find(directions.begin(), directions.end(), enemy.direction) != directions.end();
		oppositeDirectionPossible = std::find(directions.begin(), directions.end(), oppositeDirection(enemy.direction)) != directions.end();
		if (currentDirectionPossible && oppositeDirectionPossible)
		{
			propabilities.push_back(80);
			propabilities.push_back(98);
			propabilities.push_back(100);
		}
		else if (currentDirectionPossible && !oppositeDirectionPossible)
		{
			propabilities.push_back(80);
			propabilities.push_back(90);
			propabilities.push_back(100);
		}
		else if (!currentDirectionPossible && oppositeDirectionPossible)
		{
			propabilities.push_back(49);
			propabilities.push_back(98);
			propabilities.push_back(100);
		}
		break;
	case 2:
		currentDirectionPossible = std::find(directions.begin(), directions.end(), enemy.direction) != directions.end();
		oppositeDirectionPossible = std::find(directions.begin(), directions.end(), oppositeDirection(enemy.direction)) != directions.end();
		if (currentDirectionPossible && oppositeDirectionPossible)
		{
			propabilities.push_back(98);
			propabilities.push_back(100);
		}
		else if (currentDirectionPossible && !oppositeDirectionPossible)
		{
			propabilities.push_back(80);
			propabilities.push_back(100);
		}
		else if (!currentDirectionPossible && oppositeDirectionPossible)
		{
			propabilities.push_back(98);
			propabilities.push_back(100);
		}
		break;
	case 1:
		propabilities.push_back(100);
		break;
	default:
		propabilities.push_back(100);
		break;
	}

	return propabilities;
}

std::vector<Direction> Game::getInitialDirections(Enemy& enemy)
{
	// Build array for determining a direction with certain propabilities
	std::vector<Direction> allDirections{ Direction::RIGHT, Direction::LEFT, Direction::UP, Direction::DOWN };
	std::vector<Direction> orderedDirections;
	std::vector<Direction> directions;

	float xDistance = std::abs(enemy.position[0] - Pengo->position[0]) * (2.0f / 448.0f);
	float yDistance = std::abs(enemy.position[1] - Pengo->position[1]) * (2.0f / 576.0f);

	switch (enemy.state)
	{
	case EnemyState::WANDERING:
		orderedDirections.push_back(enemy.direction);
		for (Direction d : allDirections)
		{
			if (d != enemy.direction && d != oppositeDirection(enemy.direction))
			{
				orderedDirections.push_back(d);
			}
		}
		orderedDirections.push_back(oppositeDirection(enemy.direction));

		for (int i = 0; i < orderedDirections.size(); ++i)
		{
			if (!checkCollisions(enemy, orderedDirections.at(i)))
			{
				directions.push_back(orderedDirections.at(i));
			}
		}
		break;
	case EnemyState::CHASING:

		if (xDistance >= yDistance)
		{
			//Move horizontally (x-direction)
			if (enemy.position[0] > Pengo->position[0])
			{
				//Pengo is left, so move left
				orderedDirections.push_back(Direction::LEFT);
			}
			else
			{
				orderedDirections.push_back(Direction::RIGHT);
			}

			if (enemy.position[1] > Pengo->position[1])
			{
				//Pengo is left, so move left
				orderedDirections.push_back(Direction::DOWN);
			}
			else
			{
				orderedDirections.push_back(Direction::UP);
			}
		}
		else if (xDistance < yDistance)
		{
			//Move vertically (y-direction)
			if (enemy.position[1] > Pengo->position[1])
			{
				//Pengo is left, so move left
				orderedDirections.push_back(Direction::DOWN);
			}
			else
			{
				orderedDirections.push_back(Direction::UP);
			}

			if (enemy.position[0] > Pengo->position[0])
			{
				//Pengo is left, so move left
				orderedDirections.push_back(Direction::LEFT);
			}
			else
			{
				orderedDirections.push_back(Direction::RIGHT);
			}
		}

		for (Direction d : allDirections)
		{
			if (std::find(orderedDirections.begin(), orderedDirections.end(), d) == orderedDirections.end())
			{
				orderedDirections.push_back(d);
			}
		}

		for (int i = 0; i < orderedDirections.size(); ++i)
		{
			if (!checkWallCollision(enemy, orderedDirections.at(i)))
			{
				Block* block = getCollisionBlock(enemy, orderedDirections.at(i));
				if (block == nullptr || !block->isUnbreakable)
				{
					directions.push_back(orderedDirections.at(i));
				}
			}
		}
		break;
	}

	return directions;
}

int Game::getDirectionIndex(std::vector<int> chances)
{
	int index = 0;
	int randomNumber = std::rand() % 100;
	for (int i = 0; i < chances.size(); i++)
	{
		if (randomNumber > chances.at(i))
			index++;
	}
	return index;
}

bool Game::isMovementPossible(Enemy& enemy, Direction d)
{

	return false;
}

void Game::killEnemy(Enemy* enemy)
{
	this->enemyAnimators.erase(std::remove_if(enemyAnimators.begin(), enemyAnimators.end(),
		[&](EnemyAnimator* ea) {
			return ea->enemy == enemy;
		}));
	this->Levels[this->Level].Enemies.erase(std::remove_if(this->Levels[this->Level].Enemies.begin(), this->Levels[this->Level].Enemies.end(),
		[&](Enemy* comparison) {
			return comparison == enemy;
		}));

	startClockEnemyKill = std::clock();
}

void Game::spawnEnemy()
{
	bool validEnemy = false;
	Enemy* enemy;

	while (!validEnemy)
	{
		enemy = this->Levels[this->Level].frozenEnemies.back();
		this->Levels[this->Level].frozenEnemies.pop_back();
		for (Block b : this->Levels[this->Level].Bricks)
		{
			if (b.position == enemy->position && b.state != BlockState::BROKEN && b.state != BlockState::BREAKING)
			{
				validEnemy = true;
			}

		}
		if (this->Levels[this->Level].frozenEnemies.empty() && validEnemy == false)
			return;
	}
	this->Levels[this->Level].Enemies.push_back(enemy);
	for (Block& block : this->Levels[this->Level].Bricks)
		//if (std::abs(block.position[0] - enemy->position[0]) < EPSILON && std::abs(block.position[1] - enemy->position[1]) < EPSILON)
		if(block.containedEnemy == enemy)
			block.setState(BlockState::BROKEN);
	enemyAnimators.push_back(new EnemyAnimator(enemy, 0.4f, 3.0f, 1.5f));
	enemy->setState(EnemyState::SPAWNING);

	for (Block& b : this->Levels[this->Level].Bricks)
	{
		if ((b.state != BlockState::BROKEN && b.state != BlockState::BREAKING) && b.containedEnemy != nullptr)
		{
			b.setState(BlockState::FLASHING);
		}
	}
}

bool Game::boxerExists()
{
	for (Enemy* e : this->Levels[this->Level].Enemies)
	{
		if (e->baseType == "Boxer")
			return true;
	}
	return false;
}

void Game::trySettingBoxer()
{
	for (Enemy* e : this->Levels[this->Level].Enemies)
	{
		if (e->state == EnemyState::WANDERING)
		{
			e->baseType = "Boxer";
			e->setState(EnemyState::CHASING);
			return;
		}
	}
}

void Game::initNextLevel()
{
	blockAnimators.clear();
	enemyAnimators.clear();
	
	++this->Level;
	if (this->Levels.size() <= this->Level)
	{
		std::cout << "GAME WON" << std::endl;
		PengoState = GameState::GAME_MENU;
		return;
	}

	this->Pengo = &this->Levels[this->Level].Pengo;

	this->pengoAnimator = new PengoAnimator(&this->Levels[this->Level].Pengo, 0.5f, 0.25f);
	for (Block& b : this->Levels[this->Level].Bricks)
		blockAnimators.push_back(new BlockAnimator(0.5f, 3.0f, &b));
	this->wallAnimator = new WallAnimator(&this->Levels[this->Level].BottomWall, &this->Levels[this->Level].TopWall, &this->Levels[this->Level].LeftWall, &this->Levels[this->Level].RightWall, 0.5f);
	for (Enemy* e : this->Levels[this->Level].Enemies)
	{
		enemyAnimators.push_back(new EnemyAnimator(e, 0.4f, 3.0f, 1.5f));
	}

	for (Block& b : this->Levels[this->Level].Bricks)
	{
		if ((b.state != BlockState::BROKEN && b.state != BlockState::BREAKING) && b.containedEnemy != nullptr)
		{
			b.setState(BlockState::FLASHING);
		}
	}
	for (Enemy* e : this->Levels[this->Level].Enemies)
	{
		e->setState(EnemyState::INITIAL_SPAWNING);
	}

	startClockLevel, startClockEnemyKill = std::clock();

}

bool Game::checkThreeDiamonds()
{
	int amountAdjacentDiamonds = 0;
	bool bTouchesWall = false;
	bool firstAdjacentBlockTouchesWall = false;
	bool secondAdjacentBlockTouchesWall = false;

	for (Block& b : this->Levels[this->Level].Bricks)
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

Block* Game::adjacentBlockIsDiamond(Block& b)
{
	Block* collisionBlockRight = getCollisionBlock(b, Direction::RIGHT);
	Block* collisionBlockLeft = getCollisionBlock(b, Direction::LEFT);
	Block* collisionBlockUp = getCollisionBlock(b, Direction::UP);
	Block* collisionBlockDown = getCollisionBlock(b, Direction::DOWN);
	if (collisionBlockRight != nullptr && collisionBlockRight->isUnbreakable)
		return collisionBlockRight;
	else if (collisionBlockLeft != nullptr && collisionBlockLeft->isUnbreakable)
		return collisionBlockLeft;
	else if (collisionBlockUp != nullptr && collisionBlockUp->isUnbreakable)
		return collisionBlockUp;
	else if (collisionBlockDown != nullptr && collisionBlockDown->isUnbreakable)
		return collisionBlockDown;
	return nullptr;
}

bool Game::blockTouchesWall(Block& b)
{
	
	return checkWallCollision(b, Direction::RIGHT) || checkWallCollision(b, Direction::LEFT) || checkWallCollision(b, Direction::UP) || checkWallCollision(b, Direction::DOWN);
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


