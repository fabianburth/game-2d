#pragma once

#include "../Subject.h"
#include "GameObject.h"

#include <vector>

enum class WallState { SOLID, WOBBLY };

enum class WallSide { TOP, BOTTOM, RIGHT, LEFT };

/// <summary>
/// Class which wraps several GameObjects make up a wall
/// </summary>
class Wall : public Subject<Wall> {
  public:
    WallState state = WallState::SOLID;
    WallSide side;
    std::vector<GameObject> wallComponents;

    static constexpr float WOBBLY_DURATION = 0.5f;
    float wobblyFor = 0.0f;

    /// <summary>
    /// Default Constructor
    /// </summary>
    Wall();

    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="side">side - f.e. left, if this is the wall on the left side</param>
    Wall(WallSide side);

    /// <summary>
    /// Sets the state of the wall
    /// </summary>
    /// <param name="state">Walls state</param>
    void setState(WallState state);

    /// <summary>
    /// Adds a GameObject as one component of the wall
    /// </summary>
    /// <param name="component">instance of a game object</param>
    void addWallComponent(GameObject component);

    /// <summary>
    /// Method inherited from the Subject template class to register
    /// objects as observer to be informed about updates in Walls state
    /// </summary>
    /// <param name="o">pointer to the object that shall be registered as
    /// observer</param>
    void registerObserver(Observer<Wall> *o) override;

    /// <summary>
    /// Method inherited from the Subject template class to remove
    /// objects as observer that should not be informed about
    /// updates in Walls state anymore
    /// </summary>
    /// <param name="o">pointer to the object that shall be
    /// removed as registered observer</param>
    void removeObserver(Observer<Wall> *o) override;

    /// <summary>
    /// Method inherited from Subject template class to inform
    /// all objects registered as observer about updates
    /// in Walls state
    /// </summary>
    void notifyObservers() override;

  protected:
    std::vector<Observer<Wall> *> observers;
};