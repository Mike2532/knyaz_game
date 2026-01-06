#ifndef KNYAZ_GAME_GLOBALS_H
#define KNYAZ_GAME_GLOBALS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <vector>
#include "iostream"
#include "../types.h"
#include "../ui/mainMenu/mainMenu.h"
#include "./mapObjs/gameEntity/gameEntity.h"
#include "./AnimatedObj/AnimatedObj.h"

using namespace std;

extern sf::Sprite BGSprite;
extern sf::Sprite HpIndicatorSprite;

extern bool lastTeleported;
extern sf::RectangleShape antiGravityField;

extern std::map<std::string, AnimationData> animationContainer;

extern sf::RenderWindow window;
extern GameState curState;
extern std::map<std::string, sf::Keyboard::Scancode> keymap;
extern sf::Clock globalTimer;

void initDepends();
void initVariables();

void initAntiGravityField();

#endif //KNYAZ_GAME_GLOBALS_H
