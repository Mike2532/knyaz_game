#ifndef KNYAZ_GAME_HELPMENU_H
#define KNYAZ_GAME_HELPMENU_H

#include <SFML/Graphics/Text.hpp>
#include <vector>

using namespace std;

using HelpMenu = std::vector<sf::Text>;

extern HelpMenu helpMenu;

vector<sf::Text> getHelpMenu();
void helpMenuEventsHandler(const sf::Event& event);

#endif //KNYAZ_GAME_HELPMENU_H
