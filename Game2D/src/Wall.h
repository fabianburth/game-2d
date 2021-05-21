#pragma once

#include <vector>
#include "GameObject.h"
#include "Subject.h"
#include "ResourceManager.h"

enum class WallState
{
	SOLID,
	WOBBLY
};

enum class WallSide
{
	TOP,
	BOTTOM,
	RIGHT,
	LEFT
};

class Wall: public Subject<Wall>
{
public:
	WallState state = WallState::SOLID;
	WallSide side;
	std::vector<GameObject> wallComponents;

	Wall();
	Wall(WallSide side);
	void setState(WallState state);
	void setSprite(Texture2D sprite);
	void addWallComponent(GameObject component);

	void registerObserver(Observer<Wall>* o) override;
	void removeObserver(Observer<Wall>* o) override;
	void notifyObservers() override;

private:
	std::vector<Observer<Wall>*> observers;
};