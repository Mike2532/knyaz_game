#include <SFML/Window/Event.hpp>
#include "../../globals/globals.h"
#include "../../resources/BG/BG.h"

void GameEndClickHandler() {
    curState = GameState::MAIN_MENU;
    updateBGSprite();
}

void GameEndEventsHandler(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed) {
        GameEndClickHandler();
    }
}