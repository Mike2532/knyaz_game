#include "./globals/globals.h"

void updateMainMenu(std::vector<sf::Text>& textToPrint) {
    textToPrint = {mainMenu.startText, mainMenu.settingsText, mainMenu.exitText};
}
