#include <SFML/System/Vector2.hpp>
#include "../../../globals/globals.h"
#include "../collisionChecker/checker.h"
#include "../../../globals/mapObjs/mapObjs.h"
#include "../../knyaz.h"
#include "../resources/sounds/fx/run/knyazRunFX.h"

void checkVerticalCollision(vector<GameEntity> &container) {
    sf::Vector2f knyazPos = knyaz.body.getPosition();
    sf::Vector2f knyazSize = knyaz.body.getSize();

    for (auto& obj : container) {
        const bool upCollision = isUpCollision(obj);
        const bool downCollision = isDownCollision(obj);

        if (!(upCollision || downCollision)) continue;

        if (downCollision) {
            knyaz.changeAnimation(animationContainer["falling"]);
            knyaz.isJump = false;
            knyaz.freeFallingTimer.restart();
        }

        sf::Vector2f objPos = obj.body.getPosition();
        sf::Vector2f  objSize = obj.body.getSize();

        knyazPos.y = (upCollision)
                     ? objPos.y - knyazSize.y
                     : objPos.y + objSize.y;

        knyaz.body.setPosition(knyazPos);
    }
}

void verticalMoveProcess() {
    constexpr float FREE_FALLING_SPEED_MULTIPLYER = 0.4f;
    constexpr float JUMP_POWER = 0.3f;
    constexpr float CLIMBING_SPEED_MULTIPLYER = 0.15f;

    if (knyaz.isTp) {
        return;
    }

    sf::Vector2f knyazPosition = knyaz.body.getPosition();

    if (knyaz.isFlyingUp) {
        knyazPosition.y -= 0.2f;
        knyaz.body.setPosition(knyazPosition);
        return;
    }

    if (knyaz.isClimbing) {
        float climbingOffset = (knyaz.climbingTimer.getElapsedTime().asSeconds()) * CLIMBING_SPEED_MULTIPLYER;
        knyazPosition.y += climbingOffset;
    }

    const float fallingOffset = knyaz.freeFallingTimer.getElapsedTime().asSeconds() * FREE_FALLING_SPEED_MULTIPLYER;

    if (knyaz.isFalling) {
        knyazPosition.y += fallingOffset;
        stopKnyazRunSound();
    }

    if (knyaz.isJump) {
        knyazPosition.y -= JUMP_POWER;
        if (fallingOffset >= JUMP_POWER) {
            knyaz.isJump = false;
            knyaz.changeAnimation(animationContainer["falling"]);
            knyaz.freeFallingTimer.restart();
        }
    }

    knyaz.body.setPosition(knyazPosition);
}

void verticalMove() {
    verticalMoveProcess();
    checkVerticalCollision(mapObjs);
}