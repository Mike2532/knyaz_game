#include "globals.h"
#include "string"
#include "./viewport/viewport.h"

using namespace std;

sf::Sprite BGSprite;
sf::Sprite HpIndicatorSprite;

std::map<std::string, AnimationData> animationContainer;

sf::RenderWindow window;

//TODO в прод разкомментировать
//GameState curState = GameState::MAIN_MENU;
//TODO в прод закомментировать
GameState curState = GameState::GAME_PROCESS;

bool lastTeleported = false;

sf::RectangleShape antiGravityField;

void initAntiGravityField() {
    antiGravityField.setSize({100.f * VIEW_SCALE_X, 701.f * VIEW_SCALE_Y});
    antiGravityField.setPosition({3634.f * VIEW_SCALE_X, 34.f * VIEW_SCALE_Y});
    antiGravityField.setFillColor({16, 211, 255, 120});
}

std::map<std::string, sf::Keyboard::Scancode> keymap;
sf::Clock globalTimer;