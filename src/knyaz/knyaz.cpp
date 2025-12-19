#include "knyaz.h"
#include "iostream"
#include "../globals/globals.h"

using namespace std;

extern vector<GameEntity> mapObjs;

bool isKnyazVerticalOverlap(GameEntity entity) {
    return knyaz.getRight() > entity.getLeft() && knyaz.getRight() < entity.getRight() || knyaz.getLeft() > entity.getLeft() && knyaz.getLeft() < entity.getRight();
}

void fallingCheck(bool &falling) {
    for (auto entity : mapObjs) {
        if (isKnyazVerticalOverlap(entity) && abs(knyaz.getBot() - entity.getTop()) < 0.2f) {
            falling = false;
            if (knyaz.isAlive && (entity.type == ObjsTypes::OBTACLE || entity.type == ObjsTypes::SPIKES_UP)) {
                knyaz.changeAnimation(animationContainer["death"]);
                knyaz.isAlive = false;
                knyaz.hp = 0;
            }
            break;
        }
    }
}

void checkKnyazFalling() {
    bool falling = true;
    fallingCheck(falling);

    if (knyaz.isClimbing) return;

    if (knyaz.isFalling && !falling) {
        if (!(knyaz.isMovingRight || knyaz.isMovingLeft)) knyaz.changeAnimation(animationContainer["idle"]);
        else knyaz.changeAnimation(animationContainer["run"]);
    }

    if (falling == knyaz.isFalling) return;
    if (falling && !knyaz.isJump && knyaz.isAlive) knyaz.changeAnimation(animationContainer["falling"]);
    if (falling) {
        knyaz.isFalling = true;
        knyaz.freeFallingTimer.restart();
    } else {
        knyaz.isFalling = false;
        knyaz.isJump = false;
        knyaz.isDoubleJump = false;
    }
}

bool isLeftCollision(GameEntity& entity) {
    return knyaz.getRight() > entity.getLeft() && knyaz.getLeft() < entity.getLeft();
}

bool isRightCollision(GameEntity& entity) {
    return knyaz.getLeft() < entity.getRight() && knyaz.getRight() > entity.getRight();
}

bool isUpCollision(GameEntity& entity) {
    return isKnyazVerticalOverlap(entity) && knyaz.getBot() > entity.getTop() && knyaz.getTop() < entity.getTop();
}

bool isDownCollision(GameEntity& entity) {
    return isKnyazVerticalOverlap(entity) && knyaz.getTop() < entity.getBot() && knyaz.getBot() > entity.getBot();
}

bool isKnyazUpper(GameEntity& entity) {
    return knyaz.getBot() <= entity.getTop();
}

bool isKnyazLower(GameEntity& entity) {
    return knyaz.getTop() >= entity.getBot();
}

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
            knyaz.isJump = false;
            knyaz.isDoubleJump = false;
            knyaz.isFalling = false;
        }

        if ( !(leftCollision || rightCollision)) continue;

        if (knyaz.isAlive && (obj.type == ObjsTypes::OBTACLE || obj.type == ObjsTypes::SPIKES || obj.type == ObjsTypes::SPIKES_UP)) {
            knyaz.changeAnimation(animationContainer["death"]);
            knyaz.isAlive = false;
            knyaz.hp = 0;
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
        knyaz.isJump = false;
        knyaz.isDoubleJump = false;
        knyaz.isFalling = false;
        knyaz.climbingTimer.restart();
    }
}

void checkKnyazEnemyCollision() {
    sf::Vector2f knyazPos = knyaz.body.getPosition();
    sf::Vector2f knyazSize = knyaz.body.getSize();

    for (auto &enemy : mapEnemys) {
        const bool leftCollision = isLeftCollision(enemy);
        const bool rightCollision = isRightCollision(enemy);

        if ((isKnyazLower(enemy) || isKnyazUpper(enemy)) || !(leftCollision || rightCollision)) continue;

        sf::Vector2f objPos = enemy.body.getPosition();
        sf::Vector2f  objSize = enemy.body.getSize();

        knyazPos.x = (leftCollision)
                     ? objPos.x - knyazSize.x
                     : objPos.x + objSize.x;

        knyaz.body.setPosition(knyazPos);
    }
}

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

void leftMoveProcess(const unsigned int& LEFT_CAMERA_EDGE, const float &offset) {
    constexpr int LEFT_EDGE_INDEX = 0;

    sf::Vector2f knyazPosition = knyaz.body.getPosition();

    GameEntity leftEdge = mapObjs[LEFT_EDGE_INDEX];
    sf::Vector2f leftEdgeSize = leftEdge.body.getSize();
    sf::Vector2f leftEdgePos = leftEdge.body.getPosition();

    if (knyazPosition.x >= LEFT_CAMERA_EDGE || leftEdgePos.x + leftEdgeSize.x + offset >= 0) {
        knyazPosition.x -= offset;
    } else if (knyazPosition.x < LEFT_CAMERA_EDGE) {
        for (auto& mapObj : mapObjs) {
            sf::Vector2f entityPos = mapObj.body.getPosition();
            entityPos.x += offset;
            mapObj.body.setPosition(entityPos);
        }
        for (auto& enemy : mapEnemys) {
            sf::Vector2f enemyPos = enemy.body.getPosition();
            enemyPos.x += offset;
            enemy.RIGHT_ACTIVE_EDGE += offset;
            enemy.RIGHT_PATROLING_EDGE += offset;
            enemy.LEFT_ACTIVE_EDGE += offset;
            enemy.LEFT_PATROLING_EDGE += offset;
            enemy.body.setPosition(enemyPos);
        }
        for (auto& portal : mapPortals) {
            portal.inCoords.x = portal.inCoords.x + offset;
            portal.outCoords.x = portal.outCoords.x + offset;

            sf::Vector2f inBodyPos = portal.inBody.getPosition();
            sf::Vector2f outBodyPos = portal.outBody.getPosition();
            inBodyPos.x += offset;
            outBodyPos.x += offset;
            portal.inBody.setPosition(inBodyPos);
            portal.outBody.setPosition(outBodyPos);
        }
        sf::Vector2f antiGravityPos = antiGravityField.getPosition();
        antiGravityPos.x = antiGravityPos.x + offset;
        antiGravityField.setPosition(antiGravityPos);
    }
    knyaz.body.setPosition(knyazPosition);
}

void rightMoveProcess(const unsigned int& RIGHT_CAMERA_EDGE, const float &offset, const unsigned int &SCREEN_WIDTH) {
    constexpr int RIGHT_EDGE_INDEX = 1;

    sf::Vector2f knyazPosition = knyaz.body.getPosition();

    GameEntity rightEdge = mapObjs[RIGHT_EDGE_INDEX];
    sf::Vector2f rightEdgePos = rightEdge.body.getPosition();

    if (knyazPosition.x <= RIGHT_CAMERA_EDGE || rightEdgePos.x - offset < SCREEN_WIDTH) {
        knyazPosition.x += offset;
    } else if (knyaz.isMovingRight && knyazPosition.x > RIGHT_CAMERA_EDGE) {
        for (auto& mapObj : mapObjs) {
            sf::Vector2f entityPos = mapObj.body.getPosition();
            entityPos.x -= offset;
            mapObj.body.setPosition(entityPos);
        }
        for (auto& enemy : mapEnemys) {
            sf::Vector2f enemyPos = enemy.body.getPosition();
            enemyPos.x -= offset;
            enemy.RIGHT_ACTIVE_EDGE -= offset;
            enemy.RIGHT_PATROLING_EDGE -= offset;
            enemy.LEFT_ACTIVE_EDGE -= offset;
            enemy.LEFT_PATROLING_EDGE -= offset;
            enemy.body.setPosition(enemyPos);
        }
        for (auto& portal : mapPortals) {
            portal.inCoords.x = portal.inCoords.x - offset;
            portal.outCoords.x = portal.outCoords.x - offset;

            sf::Vector2f inBodyPos = portal.inBody.getPosition();
            sf::Vector2f outBodyPos = portal.outBody.getPosition();
            inBodyPos.x -= offset;
            outBodyPos.x -= offset;
            portal.inBody.setPosition(inBodyPos);
            portal.outBody.setPosition(outBodyPos);
        }
        sf::Vector2f antiGravityPos = antiGravityField.getPosition();
        antiGravityPos.x = antiGravityPos.x - offset;
        antiGravityField.setPosition(antiGravityPos);
    }
    knyaz.body.setPosition(knyazPosition);
}

void horizontalMoveProcess(const float& elapsedTime) {
    constexpr float KNYAZ_MOVE_SPEED = 600.f;
    const float offset = KNYAZ_MOVE_SPEED * elapsedTime;

    const unsigned int SCREEN_WIDTH = sf::VideoMode::getDesktopMode().width;
    const unsigned int LEFT_CAMERA_EDGE = SCREEN_WIDTH / 5 * 2;
    const unsigned int RIGHT_CAMERA_EDGE = SCREEN_WIDTH / 5 * 2;

    if (knyaz.isMovingLeft) {
        leftMoveProcess(LEFT_CAMERA_EDGE, offset);
    } else if (knyaz.isMovingRight) {
        rightMoveProcess(RIGHT_CAMERA_EDGE, offset, SCREEN_WIDTH);
    }
}

void verticalMoveProcess() {
    constexpr float FREE_FALLING_SPEED_MULTIPLYER = 0.4f;
    constexpr float JUMP_POWER = 0.3f;
    constexpr float CLIMBING_SPEED_MULTIPLYER = 0.15f;

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

void horizontalMove(const float& elapsedTime) {
    horizontalMoveProcess(elapsedTime);
    checkHorizontalCollision(mapObjs);
}

void verticalMove() {
    verticalMoveProcess();
    checkVerticalCollision(mapObjs);
}

void knyazMove(const float& elapsedTime) {
    horizontalMove(elapsedTime);
    verticalMove();
}

sf::RectangleShape getKnyazBody() {
    constexpr float KNYAZ_X_SIZE = 45.f;
    constexpr float KNYAZ_Y_SIZE = 75.f;
    constexpr float KNYAZ_START_X = 39.f;
    constexpr float KNYAZ_START_Y = 400.f;

    sf::RectangleShape knyazBody({KNYAZ_X_SIZE, KNYAZ_Y_SIZE});
    knyazBody.setPosition({KNYAZ_START_X, KNYAZ_START_Y});
    return knyazBody;
}

void updateHpIndicator() {
    sf::Color HpColor = HpIndicatorSprite.getColor();
    HpColor.a = 255 * float (float (knyaz.MAX_HP - knyaz.hp) / knyaz.MAX_HP);
    HpIndicatorSprite.setColor(HpColor);
}

void checkKnyazPortaling() {
    const sf::Vector2f knyazPos = knyaz.body.getPosition();
    for (int i = 0; i < mapPortals.size(); i++) {
        Portal portal = mapPortals[i];
        const sf::Vector2f portalPos = portal.inCoords;
        if (abs(portalPos.x - knyazPos.x) <= 25 && abs(portalPos.y - knyazPos.y) <= 2) {
            knyaz.body.setPosition(portal.outCoords);
            if (i == mapPortals.size() - 1) {
                lastTeleported = true;
                knyaz.isFlyingUp = false;
            } else if (i == 0) {
                knyaz.isFlyingUp = true;
            }
            break;
        }
    }

    for (auto portal : mapPortals) {
        const sf::Vector2f portalPos = portal.inCoords;
        if (abs(portalPos.x - knyazPos.x) <= 25 && abs(portalPos.y - knyazPos.y) <= 2) {
            knyaz.body.setPosition(portal.outCoords);
            break;
        }
    }
}