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
            knyaz.hp += knyaz.MAX_HP / 100 * 35;
            removeBottleByCoords(obj.body.getPosition());
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

void moveProcess(
        bool isLeftMove,
        const float offset,
        const unsigned int cameraEdge,
        const unsigned int screenWidth = 0 // для правого края
) {
    int edgeIndex = (isLeftMove ? 0 : 1);
    sf::Vector2f knyazPos = knyaz.body.getPosition();
    GameEntity edge = mapObjs[edgeIndex];
    sf::Vector2f edgePos = edge.body.getPosition();
    sf::Vector2f edgeSize = edge.body.getSize();

    float signedOffset = isLeftMove ? -offset : offset;

    if ((isLeftMove && knyazPos.x >= cameraEdge) ||
        (!isLeftMove && knyazPos.x <= cameraEdge) ||
        (isLeftMove && edgePos.x + edgeSize.x + signedOffset >= 0) ||
        (!isLeftMove && edgePos.x - signedOffset < screenWidth))
    {
        knyazPos.x += signedOffset;
    } else {
        auto moveEntity = [signedOffset](auto& entity){
            sf::Vector2f pos = entity.body.getPosition();
            pos.x += -signedOffset;
            entity.body.setPosition(pos);
        };

        for (auto& obj : mapObjs) moveEntity(obj);

        for (auto& enemy : mapEnemys) {
            sf::Vector2f pos = enemy.body.getPosition();
            pos.x += -signedOffset;
            enemy.RIGHT_ACTIVE_EDGE += -signedOffset;
            enemy.RIGHT_PATROLING_EDGE += -signedOffset;
            enemy.LEFT_ACTIVE_EDGE += -signedOffset;
            enemy.LEFT_PATROLING_EDGE += -signedOffset;
            enemy.body.setPosition(pos);
        }

        for (auto& portal : mapPortals) {
            portal.inCoords.x += -signedOffset;
            portal.outCoords.x += -signedOffset;

            sf::Vector2f inPos = portal.inBody.getPosition();
            sf::Vector2f outPos = portal.outBody.getPosition();
            inPos.x += -signedOffset;
            outPos.x += -signedOffset;
            portal.inBody.setPosition(inPos);
            portal.outBody.setPosition(outPos);
        }

        sf::Vector2f agPos = antiGravityField.getPosition();
        agPos.x += -signedOffset;
        antiGravityField.setPosition(agPos);
    }

    knyaz.body.setPosition(knyazPos);
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