#ifndef KNYAZ_GAME_MAINMENUSTRUCT_H
#define KNYAZ_GAME_MAINMENUSTRUCT_H

#include <SFML/Graphics/Text.hpp>

struct MainMenu {
    sf::Text startText;
    sf::FloatRect startTextInfo;
    sf::Text settingsText;
    sf::FloatRect settingsTextInfo;
    sf::Text exitText;
    sf::FloatRect exitTextInfo;
};

#endif //KNYAZ_GAME_MAINMENUSTRUCT_H
