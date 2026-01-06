#ifndef KNYAZ_GAME_CONFIG_H
#define KNYAZ_GAME_CONFIG_H

#include <SFML/Window/Keyboard.hpp>
#include "map"
#include "string"

using namespace std;

extern map<std::string, std::string> config;
map<string, string> initConfig();
map<string, sf::Keyboard::Scancode> getKeymap();

#endif //KNYAZ_GAME_CONFIG_H