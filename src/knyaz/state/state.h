#ifndef KNYAZ_GAME_STATE_H
#define KNYAZ_GAME_STATE_H

#include <SFML/Graphics/RectangleShape.hpp>

sf::RectangleShape initKnyazBody();
void updateHpIndicator();
void checkKnyazPortaling();
void knyazMeetBossProcess();

#endif //KNYAZ_GAME_STATE_H
