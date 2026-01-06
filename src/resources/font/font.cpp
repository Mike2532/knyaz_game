#include <SFML/Graphics/Font.hpp>
#include <iostream>
#include "../../../config/config.h"

using namespace std;

sf::Font myFont;

void initFont() {
    if (!myFont.loadFromFile(config["FONT_PATH"])) {
        std::cerr << "Failed to load font: " << config["FONT_PATH"] << "\n";
    }
}
