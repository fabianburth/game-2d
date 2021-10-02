#pragma once

#include "../Constants.h"
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "../Subject.h"

/// <summary>
/// Container object for holding all state relevant for a single
/// game object entity. Each object in the game likely needs the
/// minimal of state as described within GameObject
/// </summary>
class GameObject : public Subject<GameObject> {
  public:
    std::array<float, 2> position;
    std::array<float, 4> size;

    /// <summary>
    /// Default Constructor
    /// </summary>
    GameObject();

    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="pos">position of the game object</param>
    /// <param name="size">size of the game object</param>
    GameObject(std::array<float, 2> pos, std::array<float, 4> size = {1.0f, 1.0f, 0.0f, 0.0f});

    /// <summary>
    /// Method inherited from the Subject template class to register
    /// objects as observer to be informed about updates in GameObjects state
    /// </summary>
    /// <param name="o">pointer to the object that shall be registered as
    /// observer</param>
    void registerObserver(Observer<GameObject> *o) override;

    /// <summary>
    /// Method inherited from the Subject template class to remove
    /// objects as observer that should not be informed about
    /// updates in GameObjects state anymore
    /// </summary>
    /// <param name="o">pointer to the object that shall be
    /// removed as registered observer</param>
    void removeObserver(Observer<GameObject> *o) override;

    /// <summary>
    /// Method inherited from Subject template class to inform
    /// all objects registered as observer about updates
    /// in GameObjects state
    /// </summary>
    void notifyObservers() override;

  private:
    std::vector<Observer<GameObject> *> observers;
};
