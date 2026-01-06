#ifndef KNYAZ_GAME_PORTAL_H
#define KNYAZ_GAME_PORTAL_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

struct Portal {
    sf::Vector2f inCoords;
    sf::RectangleShape inBody;

    sf::Vector2f outCoords;
    sf::RectangleShape outBody;
};

#endif //KNYAZ_GAME_PORTAL_H
