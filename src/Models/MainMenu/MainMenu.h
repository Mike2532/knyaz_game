//
// Created by Миша Чулков on 22.11.2025.
//

#ifndef KNYAZ_GAME_MAINMENU_H
#define KNYAZ_GAME_MAINMENU_H

#include <SFML/Graphics.hpp>

struct MainMenu {
    sf::Text startText;
    sf::Rect<float> startTextInfo;
    sf::Text settingsText;
    sf::Rect<float> settingsTextInfo;
    sf::Text exitText;
    sf::Rect<float> exitTextInfo;
};

#endif //KNYAZ_GAME_MAINMENU_H
