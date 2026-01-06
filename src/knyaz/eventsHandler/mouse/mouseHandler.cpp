#include <SFML/Window/Event.hpp>
#include "../globals/globals.h"
#include "./left/left.h"
#include "./right/right.h"

bool canHandle() {
    return !(knyaz.isJump || knyaz.isFalling || knyaz.isMovingLeft || knyaz.isMovingRight);
}

void mouseEventsHandler(const sf::Event& event) {
    constexpr int DAMAGE_OFFSET = 15;

    if (!canHandle()) {
        return;
    }

    if (event.mouseButton.button == sf::Mouse::Left) {
        leftMouseHandler(DAMAGE_OFFSET);
    } else if (event.mouseButton.button == sf::Mouse::Right) {
        rightMouseHandler(DAMAGE_OFFSET);
    }
}