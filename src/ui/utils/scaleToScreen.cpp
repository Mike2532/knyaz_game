#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "../../globals/globals.h"

const sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
const unsigned int SCREEN_WIDTH = desktopMode.width;
const unsigned int SCREEN_HEIGHT = desktopMode.height;

void scaleToScreen() {
    constexpr float LOGIC_W = 1440;
    constexpr float LOGIC_H = 900;

    float windowWidth = SCREEN_WIDTH;
    float windowHeight = SCREEN_HEIGHT;

    gameView.setSize(LOGIC_W, LOGIC_H);
    gameView.setCenter(LOGIC_W / 2.f, LOGIC_H / 2.f);

    float aspectRatio = LOGIC_W / LOGIC_H;
    float windowAspectRatio = windowWidth / windowHeight;

    float vpX = 0.0f;
    float vpY = 0.0f;
    float vpWidth = 1.0f;
    float vpHeight = 1.0f;

    if (windowAspectRatio > aspectRatio) {
        vpHeight = aspectRatio / windowAspectRatio;
        vpY = (1.0f - vpHeight) / 2.0f;
    } else {
        vpWidth = windowAspectRatio / aspectRatio;
        vpX = (1.0f - vpWidth) / 2.0f;
    }

    gameView.setViewport(sf::FloatRect(vpX, vpY, vpWidth, vpHeight));

    UIView.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    UIView.setCenter(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
    UIView.setViewport({0.f, 0.f, 1.f, 1.f});

    window.setView(gameView);
}