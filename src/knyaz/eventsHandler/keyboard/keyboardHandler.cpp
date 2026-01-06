#include "../globals/globals.h"
#include "../globals/mapEnemys/mapEnemys.h"
#include "../globals/mapEnemys/Enemy/Enemy.h"
#include "../../knyaz.h"

void jumpHandler() {
    if (knyaz.isClimbing) {
        return;
    }
    if (knyaz.isJump && !(knyaz.isDoubleJump)) {
        knyaz.actionsHistory.clear();
        knyaz.isDoubleJump = true;
        knyaz.changeAnimation(animationContainer["jump"]);
        knyaz.freeFallingTimer.restart();
        if (knyaz.isClimbing) knyaz.isClimbing = false;
    } else if (!knyaz.isJump && !knyaz.isDoubleJump) {
        if (knyaz.actionsHistory.size() == 1 && knyaz.actionsHistory[0] == "ea") {
            knyaz.actionsHistory.emplace_back("jmp");
        }
        knyaz.isJump = true;
        knyaz.changeAnimation(animationContainer["jump"]);
        knyaz.freeFallingTimer.restart();
        if (knyaz.isClimbing) knyaz.isClimbing = false;
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

    for (auto& enemy : mapEnemys) {
        if (enemy.getRight() >=  SCREEN_W || enemy.getLeft() <= 0) {
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
}

void rageHandler() {
    constexpr int DAMAGE_OFFSET = 15;

    if (!(knyaz.isJump || knyaz.isFalling || knyaz.isMovingLeft || knyaz.isMovingRight)) {
        for (auto &enemy : mapEnemys) {
            if ((enemy.isNearLeftKnyaz  && !knyaz.isLeftOrented) || (enemy.isNearRightKnyaz &&  knyaz.isLeftOrented)) {
                knyaz.rageCounter = 0;
                knyaz.changeAnimation(animationContainer["heavyAttack"]);
                sf::Vector2f enemyPos = enemy.body.getPosition();
                enemyPos.x += knyaz.isLeftOrented ? -DAMAGE_OFFSET : DAMAGE_OFFSET;
                enemy.body.setPosition(enemyPos);
                enemy.takenDamage += knyaz.rageAttackPower;
                enemy.objSprite.setColor(sf::Color::Red);
                knyaz.attackTimer.restart();
            }
        }
    }
}

void keyboardEventsHandler() {
    if (isJumpEvent()) {
        jumpHandler();
    } else if (isClimbingEvent()) {
        climbingHandler();
    } else if (isFocusEvent()) {
        focusHandler();
    } else if (isRageEvent()) {
        rageHandler();
    }
}