#pragma once

#include "../Constants.h"
#include "DisplayBlock.h"
#include "ResourceManager.h"

#include <ctype.h>
#include <string>
#include <vector>


/// <summary>
/// Wrapper class for DisplayBlocks if information has to be shown
/// that needs more space then one block (= 1 unit width and 1 unit height)
/// </summary>
class GameInformation {
  public:
    std::array<float, 2> position;
    unsigned int amountDisplayBlocks;
    std::array<float, 4> size;

    std::string text;
    std::vector<DisplayBlock *> displayBlocks;

    /// <summary>
    /// Default Constructor
    /// </summary>
    GameInformation();

    /// <summary>
    /// Constructor
    /// </summary>
    /// <param name="position">position of the displayed information</param>
    /// <param name="size">size of the information</param>
    /// <param name="amountDisplayBlocks">amount of blocks</param>
    GameInformation(std::array<float, 2> position, std::array<float, 4> size, int amountDisplayBlocks);

    /// <summary>
    /// Converts strings into display elements if respective sprites are available
    /// </summary>
    /// <param name="text">the string to be converted</param>
    void show(std::string text);
};
