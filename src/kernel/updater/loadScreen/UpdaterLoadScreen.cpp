#include "./globals/globals.h"
#include "./resources/BG/BG.h"

constexpr float LOADING_DURATION = 5.f;

void updateLoadScreen() {
    if (globalTimer.getElapsedTime().asSeconds() < LOADING_DURATION) {
        return;
    }
    curState = GameState::LOAD_SCREEN_2;
    updateBGSprite();
}