#include "Wall.h"

Wall::Wall()
{
}

Wall::Wall(WallSide side)
    :side{side}
{
}

void Wall::setState(WallState state)
{
    if (this->state != state)
    {
        this->state = state;
        this->notifyObservers();
    }
}

//void Wall::setSprite(Texture2D sprite)
//{
//    for (GameObject& wallComponent : wallComponents)
//    {
//        wallComponent.sprite = sprite;
//    }
//}

void Wall::addWallComponent(GameObject component)
{
    wallComponents.push_back(component);
}

void Wall::registerObserver(Observer<Wall>* o)
{
	observers.push_back(o);
}

void Wall::removeObserver(Observer<Wall>* o)
{
    observers.erase(std::remove_if(observers.begin(), observers.end(),
        [&](Observer<Wall>* comparison) {
            return comparison == o;
        }));
}

void Wall::notifyObservers()
{
    for (Observer<Wall>* observer : observers)
    {
        observer->update(this);
    }
}
