#include "../globals/globals.h"
#include "../globals/mapEnemys/mapEnemys.h"
#include "../../knyaz.h"
#include "../resources/sounds/fx/run/knyazRunFX.h"
#include "../resources/sounds/fx/rage/rage.h"
#include "../resources/sounds/fx/tp/tp.h"

bool canHandleJMP() {
    return (
        knyaz.jumpCounter < knyaz.MAX_JUMP_COUNTER && (
            knyaz.curJMPState == jumpStates::base ||
            knyaz.curJMPState == jumpStates::oneJump ||
            knyaz.curJMPState == jumpStates::falling
       )
    );
}

void jumpHandler() {
    if (knyaz.isClimbing || !canHandleJMP()) {
        return;
    }

    if (knyaz.jumpCounter == 0) {
        knyaz.curJMPState = jumpStates::oneJump;
    } else if (knyaz.jumpCounter == 1) {
        knyaz.curJMPState = jumpStates::secondJump;
    }
    knyaz.jumpCounter++;
    knyaz.changeAnimation(animationContainer["jump"]);
    knyaz.freeFallingTimer.restart();

    if (knyaz.actionsHistory.size() == 1 && knyaz.actionsHistory[0] == "ea") {
        knyaz.actionsHistory.emplace_back("jmp");
    } else {
        knyaz.actionsHistory.clear();
    }
}

bool isJumpEvent() {
    return sf::Keyboard::isKeyPressed(keymap["JUMP_KEY"]) || sf::Keyboard::isKeyPressed(keymap["ALTER_JUMP_KEY"]);
}

bool isClimbingEvent() {
    return sf::Keyboard::isKeyPressed(keymap["CLIMBING_KEY"]) && knyaz.isFalling && !knyaz.isClimbing;
}

bool isFocusEvent() {
    return sf::Keyboard::isKeyPressed(keymap["FOCUS_KEY"]) && knyaz.focusCounter == knyaz.MAX_FOCUS_COUNTER;
}

bool isRageEvent() {
    return sf::Keyboard::isKeyPressed(keymap["RAGE_KEY"]) && knyaz.rageCounter == knyaz.MAX_RAGE_COUNTER;
}

void climbingHandler() {
    knyaz.isClimbing = true;
    knyaz.climbingTimer.restart();
}

void focusHandler() {
    constexpr float SCREEN_W = 1440.f;
    constexpr float MAX_TP_RANGE = 700.f;

    float minDist = INT_MAX;
    Enemy* closestEnemy = nullptr;

    auto viewCenter = gameView.getCenter();
    auto viewSize = gameView.getSize();

    auto leftEdge = viewCenter.x - viewSize.x / 2;
    auto rightEdge = viewCenter.x + viewSize.x / 2;

    for (auto& enemy : mapEnemys) {
        if (enemy.getRight() >= rightEdge || enemy.getLeft() <= leftEdge) {
            continue;
        }
        float dx = abs(enemy.getLeft() - knyaz.getLeft());
        float dy = abs(enemy.getTop() - knyaz.getTop());
        float distanse = sqrt(dx * dx + dy * dy);
        if (distanse < minDist) {
            minDist = distanse;
            closestEnemy = &enemy;
        }
    }

    if (minDist > MAX_TP_RANGE) {
        return;
    }

    knyaz.focusCounter = 0;
    sf::Vector2f enemyPos = closestEnemy->body.getPosition();
    sf::Vector2f knyazPos = knyaz.body.getPosition();
    sf::Vector2f knyazSize = knyaz.body.getSize();
    knyazPos.x = enemyPos.x - knyazSize.x;
    knyazPos.y = enemyPos.y;
    knyaz.body.setPosition(knyazPos);

    knyaz.changeAnimation(animationContainer["idle"]);
    playTpSound();
}

bool isKnyazJumping() {
    return knyaz.curJMPState == jumpStates::oneJump || knyaz.curJMPState == jumpStates::secondJump;
}

bool canHandleRage(const Enemy& enemy) {
    return enemy.isNearLeftKnyaz  && !knyaz.isLeftOrented || enemy.isNearRightKnyaz &&  knyaz.isLeftOrented;
}

void rageHandler() {
    constexpr int DAMAGE_OFFSET = 15;

    if (isKnyazJumping() || knyaz.isFalling || knyaz.isMovingLeft || knyaz.isMovingRight) {
        return;
    }

    for (auto &enemy : mapEnemys) {
        if (!canHandleRage(enemy)) {
            continue;
        }

        knyaz.rageCounter = 0;
        knyaz.changeAnimation(animationContainer["heavyAttack"]);
        sf::Vector2f enemyPos = enemy.body.getPosition();
        enemyPos.x += knyaz.isLeftOrented ? -DAMAGE_OFFSET : DAMAGE_OFFSET;
        enemy.body.setPosition(enemyPos);
        enemy.takenDamage += knyaz.rageAttackPower;
        enemy.objSprite.setColor(sf::Color::Red);
        knyaz.attackTimer.restart();
        playRageSound();
    }
}

void keyboardEventsHandler() {
    bool isJump = isJumpEvent();
    bool isCliming = isClimbingEvent();
    bool isFocus = isFocusEvent();
    bool isRage = isRageEvent();

    if (isJump || isCliming || isFocus || isRage) {
        knyaz.isAtacking = false;
    }

    if (isJump) {
        jumpHandler();
    } else if (isCliming) {
        climbingHandler();
    } else if (isFocus) {
        focusHandler();
    } else if (isRage) {
        rageHandler();
    }
}