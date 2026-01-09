#include "../../../globals/globals.h"
#include "../collisionChecker/checker.h"
#include "../../../globals/mapObjs/mapObjs.h"
#include "../../../globals/mapPortals/mapPortals.h"
#include "../../knyaz.h"
#include "../globals/mapEnemys/mapEnemys.h"
#include "../globals/bottle/bottle.h"
#include "../resources/sounds/fx/fight/fight.h"
#include "../resources/sounds/fx/landing/knyazLandingFX.h"
#include "../resources/sounds/fx/wind/wind.h"

void checkHorizontalCollision(vector<GameEntity> &container) {
    sf::Vector2f knyazPos = knyaz.body.getPosition();
    sf::Vector2f knyazSize = knyaz.body.getSize();

    bool prevClimbed = knyaz.isClimbing;
    bool leftClimb = false;
    bool rightClimb = false;

    for (auto& obj : container) {
        const bool leftCollision = isLeftCollision(obj);
        const bool rightCollision = isRightCollision(obj);

        if ((isKnyazLower(obj) || isKnyazUpper(obj))) continue;

        sf::Vector2f objPos = obj.body.getPosition();
        sf::Vector2f  objSize = obj.body.getSize();

        leftClimb = leftClimb || (abs((knyazPos.x + knyazSize.x) - objPos.x) <= 2 && obj.type == ObjsTypes::WALL && !knyaz.isLeftOrented);
        rightClimb = rightClimb || (abs((knyazPos.x - 1) - (objPos.x + objSize.x)) <= 2 && obj.type == ObjsTypes::WALL && knyaz.isLeftOrented);

        if (knyaz.isClimbing && (leftClimb || rightClimb)) {
            knyaz.changeAnimation(animationContainer["wallHang"]);
            knyaz.curJMPState = jumpStates::base;
            knyaz.jumpCounter = 0;
            knyaz.isFalling = false;
        }

        if (!(leftCollision || rightCollision)) continue;

        if (knyaz.isAlive && (obj.type == ObjsTypes::OBTACLE || obj.type == ObjsTypes::SPIKES || obj.type == ObjsTypes::SPIKES_UP)) {
            knyaz.changeAnimation(animationContainer["death"]);
            knyaz.isAlive = false;
            knyaz.hp = 0;
            stopWindSound();
            playRandomFlashSound();
            playRandomLandingSound();
        }

        if (knyaz.isAlive && obj.type == ObjsTypes::BOTTLE) {
            bottleProcess(obj);
        }

        knyazPos.x = (leftCollision)
                     ? objPos.x - knyazSize.x
                     : objPos.x + objSize.x;

        knyaz.body.setPosition(knyazPos);
    }

    knyaz.isClimbing = leftClimb || rightClimb;
    if (knyaz.isClimbing && !prevClimbed) {
        knyaz.changeAnimation(animationContainer["wallHang"]);
        knyaz.curJMPState = jumpStates::base;
        knyaz.jumpCounter = 0;
        knyaz.isFalling = false;
        knyaz.climbingTimer.restart();
    }
}

void updateCamera(float knyazX, float levelLeft, float levelRight) {
    constexpr float LOGIC_W = 1440;
    constexpr float LOGIC_H = 900;

    const float CAMERA_MARGIN = 600.f;

    float viewHalfWidth = LOGIC_W / 2.f;
    float currentCenterX = gameView.getCenter().x;

    if (knyazX < currentCenterX - viewHalfWidth + CAMERA_MARGIN) {
        currentCenterX = knyazX + viewHalfWidth - CAMERA_MARGIN;
    }
    else if (knyazX > currentCenterX + viewHalfWidth - CAMERA_MARGIN) {
        currentCenterX = knyazX - viewHalfWidth + CAMERA_MARGIN;
    }

    currentCenterX = std::max(currentCenterX, levelLeft + viewHalfWidth);
    currentCenterX = std::min(currentCenterX, levelRight - viewHalfWidth);

    gameView.setCenter(currentCenterX, LOGIC_H / 2.f);
    window.setView(gameView);
}

void moveProcess(
        bool isLeftMove,
        const float offset,
        const unsigned int cameraEdge,
        const unsigned int screenWidth = 0 // для правого края
) {
    float levelLeft = mapObjs[0].getRight();
    float levelRight = mapObjs[1].getLeft();

    float signedOffset = isLeftMove ? -offset : offset;

    sf::Vector2f knyazPos = knyaz.body.getPosition();
    knyazPos.x += signedOffset;
    knyaz.body.setPosition(knyazPos);

    updateCamera(knyazPos.x, levelLeft, levelRight);
}

void horizontalMoveProcess(const float& elapsedTime) {
    constexpr float KNYAZ_MOVE_SPEED = 600.f;
    const float offset = KNYAZ_MOVE_SPEED * elapsedTime;

    const unsigned int SCREEN_WIDTH = sf::VideoMode::getDesktopMode().width;
    const unsigned int LEFT_CAMERA_EDGE = SCREEN_WIDTH / 5 * 2;
    const unsigned int RIGHT_CAMERA_EDGE = SCREEN_WIDTH / 5 * 2;

    if (knyaz.isMovingLeft) {
        moveProcess(true, offset, LEFT_CAMERA_EDGE);
    } else if (knyaz.isMovingRight) {
        moveProcess(false, offset, RIGHT_CAMERA_EDGE, SCREEN_WIDTH);
    }
}

void horizontalMove(const float& elapsedTime) {
    horizontalMoveProcess(elapsedTime);
    checkHorizontalCollision(mapObjs);
}