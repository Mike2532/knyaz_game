#ifndef KNYAZ_GAME_UI_H
#define KNYAZ_GAME_UI_H
#include "./uiStruct.h"

extern UI ui;

extern sf::Texture HpIndicatorTexture;

void initUITextures();
void initUI(pair<const int, const int> screenSize);
void updateUI();

#endif //KNYAZ_GAME_UI_H
