#include <SFML/Window/VideoMode.hpp>
#include "globals.h"

const sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
const unsigned int SCREEN_WIDTH = desktopMode.width;
const unsigned int SCREEN_HEIGHT = desktopMode.height;

const unsigned int BG_WIDTH = 1097;
const unsigned int BG_HEIGHT = 900;

constexpr float LOGIC_W = 1440;
constexpr float LOGIC_H = 900;

void drawGameProcessBG() {
    float bgScale = LOGIC_H / BG_HEIGHT;
    float bgWidth = BG_WIDTH * bgScale;

    int numCopies = static_cast<int>(ceil(LOGIC_W / bgWidth)) + 1;

    BGSprite.setScale(bgScale, bgScale);

    for (int i = 0; i < numCopies; i++) {
        BGSprite.setPosition(i * bgWidth, 0);
        window.draw(BGSprite);
    }
}

void drawMenuBG() {
    auto texSize = BGSprite.getTexture()->getSize();

    float bgWidth  = static_cast<float>(texSize.x);
    float bgHeight = static_cast<float>(texSize.y);

    float scaleX = LOGIC_W / bgWidth;
    float scaleY = LOGIC_H / bgHeight;

    BGSprite.setScale(scaleX, scaleY);
    BGSprite.setPosition(0.f, 0.f);

    window.draw(BGSprite);
}

void drawBG() {
    if (curState == GameState::GAME_PROCESS) {
        drawGameProcessBG();
        return;
    }
    drawMenuBG();
}