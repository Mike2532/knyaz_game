#ifndef KNYAZ_GAME_BOTTLE_H
#define KNYAZ_GAME_BOTTLE_H

#include "../mapObjs/gameEntity/gameEntity.h"

int getBottleSpawnChanse();
void removeBottleByCoords(sf::Vector2f coords);
void spawnBottle(sf::Vector2f coords);
void bottleProcess(GameEntity& bottleEntity);

#endif //KNYAZ_GAME_BOTTLE_H
