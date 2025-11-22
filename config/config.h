//
// Created by Миша Чулков on 14.11.2025.
//

#ifndef KNYAZ_GAME_CONFIG_H
#define KNYAZ_GAME_CONFIG_H

#include "map"
#include "string"

using namespace std;

map<string, string> initConfig();
map<string, sf::Keyboard::Scancode> getKeymap();

#endif //KNYAZ_GAME_CONFIG_H