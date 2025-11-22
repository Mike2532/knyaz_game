//
// Created by Миша Чулков on 22.11.2025.
//

#ifndef KNYAZ_GAME_KNYAZ_H
#define KNYAZ_GAME_KNYAZ_H

#include <SFML/Graphics.hpp>

struct Knyaz {
    sf::RectangleShape body;
    bool isMovingLeft = false;
    bool isMovingRight = false;
};


#endif //KNYAZ_GAME_KNYAZ_H