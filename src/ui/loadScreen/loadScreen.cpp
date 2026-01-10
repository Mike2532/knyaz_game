#include "../../globals/globals.h"
#include "../../resources/BG/BG.h"
#include "../../knyaz/knyaz.h"
#include "../../knyaz/state/state.h"

void LoadScreenClickHandler() {
    globalTimer.restart();
    knyaz.freeFallingTimer.restart();
    knyaz.body = initKnyazBody();
    knyaz.isTp = false;

    curState = GameState::GAME_PROCESS;
    updateBGSprite();
}

void LoadScreenEventsHandler(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed) {
        LoadScreenClickHandler();
    }
}