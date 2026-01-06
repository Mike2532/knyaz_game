#ifndef KNYAZ_GAME_GAMEENTITY_H
#define KNYAZ_GAME_GAMEENTITY_H

#include <SFML/Graphics/RectangleShape.hpp>
#include "../../../types.h"

struct GameEntity {
    sf::RectangleShape body;
    ObjsTypes type;
    float getTop();
    float getBot();
    float getLeft();
    float getRight();
};

#endif //KNYAZ_GAME_GAMEENTITY_H
