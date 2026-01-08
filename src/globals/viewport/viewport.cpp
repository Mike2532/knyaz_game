#include <SFML/Window/VideoMode.hpp>

using namespace std;

sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
unsigned int SCREEN_WIDTH = desktopMode.width;
unsigned int SCREEN_HEIGHT = desktopMode.height;

unsigned int BG_WIDTH = 1097;
unsigned int BG_HEIGHT = 900;

//unsigned int LOGICAL_W = 1920;
//unsigned int LOGICAL_H = 1080;

unsigned int LOGICAL_W = SCREEN_WIDTH;
unsigned int LOGICAL_H = SCREEN_HEIGHT;

unsigned int GAME_W = 1440;
unsigned int GAME_H = 900;

float VIEW_SCALE_X = static_cast<float>(LOGICAL_W) / static_cast<float>(GAME_W);
float VIEW_SCALE_Y = static_cast<float>(LOGICAL_H) / static_cast<float>(GAME_H);

pair<const float, const float> VIEW_SCALE = make_pair(VIEW_SCALE_X, VIEW_SCALE_Y);
