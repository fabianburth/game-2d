#include "GameInformation.h"

GameInformation::GameInformation() {}

GameInformation::GameInformation(std::array<float, 2> position, std::array<float, 4> size, int amountDisplayBlocks) :
    position{position}, amountDisplayBlocks{static_cast<unsigned int>(amountDisplayBlocks)}, size{size} {
    for (int i = 0; i < amountDisplayBlocks; ++i) {
        displayBlocks.push_back(new DisplayBlock({position[0] - i * (0.5f * Constants::WIDTH_UNIT), position[1]}, size,
                                                 ResourceManager::getTexture("placeholder")));
    }
}

void GameInformation::show(std::string text) {
    if (text.empty() || text.length() > amountDisplayBlocks)
        return;

    for (unsigned int i = 0; i < text.length(); ++i) {
        std::string c{text.at(i)};
        if (text == "1P" && c == "1")
            c = "One";
        displayBlocks.at(text.length() - 1 - i)->sprite = ResourceManager::getTexture(c);
    }
}
