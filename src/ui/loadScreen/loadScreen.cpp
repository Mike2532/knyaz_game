#include "../../globals/globals.h"
#include "../../resources/BG/BG.h"

void LoadScreenClickHandler() {
    globalTimer.restart();
    curState = GameState::GAME_PROCESS;
    updateBGSprite();
}

void LoadScreenEventsHandler(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed) {
        LoadScreenClickHandler();
    }
}