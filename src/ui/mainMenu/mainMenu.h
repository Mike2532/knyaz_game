#ifndef KNYAZ_GAME_MAINMENU_H
#define KNYAZ_GAME_MAINMENU_H

#include <SFML/Graphics/Text.hpp>
#include "./mainMenuStruct.h"

extern MainMenu mainMenu;

MainMenu getMainMenu();
void mainMenuEventsHandler(const sf::Event& event);

#endif //KNYAZ_GAME_MAINMENU_H
