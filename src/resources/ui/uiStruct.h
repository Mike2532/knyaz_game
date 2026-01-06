#ifndef KNYAZ_GAME_UISTRUCT_H
#define KNYAZ_GAME_UISTRUCT_H

#include <SFML/Graphics/RectangleShape.hpp>

struct UI {
    sf::RectangleShape focusOutline;
    sf::RectangleShape focusFill;

    sf::RectangleShape rageOutline;
    sf::RectangleShape rageFill;
};

#endif //KNYAZ_GAME_UISTRUCT_H
