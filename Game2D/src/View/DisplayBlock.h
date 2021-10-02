#pragma once

#include "Texture.h"

#include <array>

/// <summary>
/// Container class to hold the data of any object that should be displayed
/// that doesnt have a dedicated view class
/// </summary>
class DisplayBlock {
  public:
    // bottom left position of the block
    //  |-----|
    //  |     |
    //  x-----|
    std::array<float, 2> position;
    std::array<float, 4> size;
    Texture2D sprite;

    /// <summary>
    /// Default Constructor
    /// </summary>
    DisplayBlock();

    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="position">position of the display object</param>
    /// <param name="size">size of the display object</param>
    /// <param name="sprite">sprite to be shown</param>
    DisplayBlock(std::array<float, 2> position, std::array<float, 4> size, Texture2D sprite);
};
