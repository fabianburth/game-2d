#pragma once

#include <vector>
#include "GameObject.h"
#include "../Subject.h"
//#include "../View/ResourceManager.h"

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

	static constexpr float WOBBLY_DURATION = 0.5f;
	float wobblyFor = 0.0f;

	Wall();
	Wall(WallSide side);
	void setState(WallState state);
	//void setSprite(Texture2D sprite);
	void addWallComponent(GameObject component);

	void registerObserver(Observer<Wall>* o) override;
	void removeObserver(Observer<Wall>* o) override;
	void notifyObservers() override;

protected:
	std::vector<Observer<Wall>*> observers;
};