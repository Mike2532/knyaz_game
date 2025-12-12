#ifndef KNYAZ_GAME_KNYAZ_H
#define KNYAZ_GAME_KNYAZ_H

#pragma once
#include "../types.h"

void knyazMove(const float& elapsedTime);
sf::RectangleShape getKnyazBody();
void checkKnyazFalling();
void checkKnyazEnemyCollision();
void updateHpIndicator();

#endif //KNYAZ_GAME_KNYAZ_H