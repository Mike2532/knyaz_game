#include "knyaz.h"
#include "iostream"
#include "../globals/globals.h"

using namespace std;

extern vector<GameEntity> mapObjs;

bool isKnyazVerticalOverlap(GameEntity entity) {
    return knyaz.getRight() > entity.getLeft() && knyaz.getRight() < entity.getRight() || knyaz.getLeft() > entity.getLeft() && knyaz.getLeft() < entity.getRight();
}

void fallingCheck(bool &falling, vector<GameEntity> &container) {
    for (auto entity : container) {
        if (isKnyazVerticalOverlap(entity) && abs(knyaz.getBot() - entity.getTop()) < 0.2f) {
            falling = false;
            if (entity.type == ObjsTypes::OBTACLE && knyaz.isAlive) {
                knyaz.changeAnimation(animationContainer["death"]);
                knyaz.isAlive = false;
            }
            break;
        }
    }
}

void checkKnyazFalling() {
    if (knyaz.isClimbing) return;

    bool falling = true;
    fallingCheck(falling, mapObjs);

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

    bool climbed = false;

    int i = 0;

    for (auto& obj : container) {
        const bool leftCollision = isLeftCollision(obj);
        const bool rightCollision = isRightCollision(obj);

        if ((isKnyazLower(obj) || isKnyazUpper(obj))) continue;

        sf::Vector2f objPos = obj.body.getPosition();
        sf::Vector2f  objSize = obj.body.getSize();

        bool leftClimb = abs((knyazPos.x + knyazSize.x) - objPos.x) <= 3;
        bool rightClimb = abs((knyazPos.x - 1) - (objPos.x + objSize.x)) <= 3;

        if (knyaz.isClimbing && (leftClimb || rightClimb)) {
            knyaz.changeAnimation(animationContainer["wallHang"]);
            knyaz.isJump = false;
            knyaz.isDoubleJump = false;
            knyaz.isFalling = false;
            climbed = true;
        }

        if ( !(leftCollision || rightCollision)) continue;

        if (knyaz.isAlive && (obj.type == ObjsTypes::OBTACLE || obj.type == ObjsTypes::SPIKES || obj.type == ObjsTypes::SPIKES_UP)) {
            knyaz.changeAnimation(animationContainer["death"]);
            knyaz.isAlive = false;
        }

        knyazPos.x = (leftCollision)
                     ? objPos.x - knyazSize.x
                     : objPos.x + objSize.x;

        knyaz.body.setPosition(knyazPos);
    }

    if (knyaz.isClimbing && !climbed) {
        knyaz.isClimbing = false;
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
    constexpr float JUMP_POWER = 0.25f;

    sf::Vector2f knyazPosition = knyaz.body.getPosition();

    float fallingOffset = knyaz.freeFallingTimer.getElapsedTime().asSeconds() * FREE_FALLING_SPEED_MULTIPLYER;

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
    constexpr float KNYAZ_SIDE_SIZE = 80.f;
    constexpr float KNYAZ_START_X = 39.f;
    constexpr float KNYAZ_START_Y = 400.f;

    sf::RectangleShape knyazBody({KNYAZ_SIDE_SIZE, KNYAZ_SIDE_SIZE});
    knyazBody.setPosition({KNYAZ_START_X, KNYAZ_START_Y});
    return knyazBody;
}