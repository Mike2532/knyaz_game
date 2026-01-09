#ifndef KNYAZ_GAME_PORTALPARAM_H
#define KNYAZ_GAME_PORTALPARAM_H

#include <SFML/System/Vector2.hpp>

struct PortalParam {
    sf::Vector2f inCoords;
    sf::Vector2f outCoords;
    sf::Vector2f inBodySize;
    sf::Vector2f inBodyPos;
    sf::Vector2f outBodySize;
    sf::Vector2f outBodyPos;
};

#endif //KNYAZ_GAME_PORTALPARAM_H
