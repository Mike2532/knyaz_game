#include <SFML/Window/Event.hpp>
#include "../globals/globals.h"
#include "./left/left.h"
#include "./right/right.h"
#include "../knyaz/knyaz.h"
#include "../../../resources/sounds/fx/fight/fight.h"

bool canHandle() {
    return !(knyaz.isJump || knyaz.isFalling || knyaz.isMovingLeft || knyaz.isMovingRight || knyaz.isAtacking);
}

void mouseEventsHandler(const sf::Event& event) {
    constexpr int DAMAGE_OFFSET = 15;

    if (!canHandle()) {
        return;
    }

    bool isLeft = event.mouseButton.button == sf::Mouse::Left;
    bool isRight = event.mouseButton.button == sf::Mouse::Right;

    if (isLeft || isRight) {
        knyaz.isAtacking = true;

        playRandomAirSound();

        if (isLeft) {
            leftMouseHandler(DAMAGE_OFFSET);
        } else if (isRight) {
            rightMouseHandler(DAMAGE_OFFSET);
        }
    }
}