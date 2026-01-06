#ifndef KNYAZ_GAME_UI_H
#define KNYAZ_GAME_UI_H
#include "./uiStruct.h"

extern UI ui;

extern sf::Texture HpIndicatorTexture;

void initUITextures();
void initUI();
void updateUI();

#endif //KNYAZ_GAME_UI_H
