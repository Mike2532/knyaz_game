#include "../globals/mapObjs/gameEntity/gameEntity.h"
#include "../globals/globals.h"
#include "./knyaz.h"

using namespace std;

Knyaz knyaz;

void Knyaz::textureUpdate() {
    constexpr int STRIP_FRAME_OFFSET = 120;
    constexpr int NORMAL_BASE_X = 27 + 17;
    constexpr int ATTACK_BASE_X = 40;

    constexpr int NORMAL_W = 43;
    constexpr int NORMAL_H = 40;
    constexpr int ATTACK_W = 65;
    constexpr int ATTACK_H = 45;

    constexpr int NORMAL_TOP = 40;
    constexpr int ATTACK_TOP = 35;

    objSprite.setTexture(animationData.animationTexture);
    if (animationData.animationType == AnimationTypes::ATTACK) {
        objSprite.setTextureRect(sf::IntRect(
                STRIP_FRAME_OFFSET * animationFrameNumber + ATTACK_BASE_X - 15.f,
                ATTACK_TOP,
                ATTACK_W + 15.f,
                ATTACK_H
        ));

        if (animationFrameNumber == animationData.animationFrames - 1) {
            if (isAlive) changeAnimation(animationContainer["idle"]);
            objSprite.setTextureRect(sf::IntRect(
                    STRIP_FRAME_OFFSET * animationFrameNumber + NORMAL_BASE_X - 15.f,
                    NORMAL_TOP,
                    NORMAL_W  + 15.f,
                    NORMAL_H
            ));
            knyaz.isAtacking = false;
        }
    } else {
        objSprite.setTextureRect(sf::IntRect(
                STRIP_FRAME_OFFSET * animationFrameNumber + NORMAL_BASE_X  - 15.f,
                NORMAL_TOP,
                NORMAL_W + 15.f,
                NORMAL_H
        ));
    }
    isAttackFinished = true;
    float scaleX = 2.f;
    float scaleY = 2.f;

    if (isLeftOrented) {
        scaleX *= -1;
        if (!isSpriteLeftOrented) isSpriteLeftOrented = true;
    } else if (isSpriteLeftOrented) {
        isSpriteLeftOrented = false;
    }

    objSprite.setScale(scaleX, scaleY);
}

void Knyaz::spritePositionUpdate() {
    sf::Vector2f pos = body.getPosition();
    pos.x -= 30;
    pos.y -= 5;
    if (animationData.animationType == AnimationTypes::ATTACK) {
        pos.y -= 10;
    }

    if (isSpriteLeftOrented) {
        pos.x += 105;
    }
    objSprite.setPosition(pos);
}

void Knyaz::takeDamage() {
    constexpr float damageMilliseconds = 400;
    if (takenDamage != 0 && damageTimer.getElapsedTime().asMilliseconds() >= damageMilliseconds) {
        rageCounter = min(rageCounter + 1, MAX_RAGE_COUNTER);
        objSprite.setColor(sf::Color::White);
        takenDamage = 0;
    }
}

void Knyaz::tpProcess() {
    if (!isTp || tpTimer.getElapsedTime().asMilliseconds() <= 150) {
        return;
    }

    knyaz.body.setPosition({knyaz.body.getPosition().x, -100});

    if (tpTimer.getElapsedTime().asMilliseconds() >= 450) {
        body.setPosition(tpCoords);
        isTp = false;
    }
}

void Knyaz::stopRun() {
    isMovingRight = false;
    isMovingLeft = false;
    curJMPState = jumpStates::base;
    jumpCounter = 0;
}

void Knyaz::dieProcess() {
    changeAnimation(animationContainer["death"]);
    isAlive = false;
    hp = 0;
    stopRun();
}