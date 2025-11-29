#include "knyaz.h"
#include "iostream"
#include "../globals/globals.h"


using namespace std;

extern vector<GameEntity> mapObjs;

bool isLeftCollision(GameEntity& entity) {
    return knyaz.getRight() > entity.getLeft() && knyaz.getLeft() < entity.getLeft();
}

bool isRightCollision(GameEntity& entity) {
    return knyaz.getLeft() < entity.getRight() && knyaz.getRight() > entity.getRight();
}

bool isUpCollision(GameEntity& entity) {
    bool a = knyaz.getRight() > entity.getLeft() && knyaz.getRight() < entity.getRight();
    bool b = knyaz.getLeft() > entity.getLeft() && knyaz.getLeft() < entity.getRight();
    bool c = knyaz.getBot() > entity.getTop() && knyaz.getTop() < entity.getTop();

    return (a || b) && c;
}

bool isDownCollision(GameEntity& entity) {
    bool a = knyaz.getRight() > entity.getLeft() && knyaz.getRight() < entity.getRight();
    bool b = knyaz.getLeft() > entity.getLeft() && knyaz.getLeft() < entity.getRight();
    bool c = knyaz.getTop() < entity.getBot() && knyaz.getBot() > entity.getBot();

    return (a || b) && c;
}

bool isKnyazUpper(GameEntity& entity) {
    return knyaz.getBot() <= entity.getTop();
}

bool isKnyazLower(GameEntity& entity) {
    return knyaz.getTop() >= entity.getBot();
}

void checkXCollision() {
    sf::Vector2f knyazPos = knyaz.body.getPosition();
    sf::Vector2f knyazSize = knyaz.body.getSize();

    for (auto& obj : mapObjs) {
        const bool leftCollision = isLeftCollision(obj);
        const bool rightCollision = isRightCollision(obj);

        if ((isKnyazLower(obj) || isKnyazUpper(obj)) || !(leftCollision || rightCollision)) continue;

        sf::Vector2f objPos = obj.body.getPosition();
        sf::Vector2f  objSize = obj.body.getSize();

        knyazPos.x = (leftCollision)
                     ? objPos.x - knyazSize.x
                     : objPos.x + objSize.x;

        knyaz.body.setPosition(knyazPos);
    }
}

void checkYCollision() {
    sf::Vector2f knyazPos = knyaz.body.getPosition();
    sf::Vector2f knyazSize = knyaz.body.getSize();

    for (auto& obj : mapObjs) {
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

void knyazMove(const float& elapsedTime) {
    const sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    const unsigned int SCREEN_WIDTH = desktopMode.width;
    const unsigned int SCREEN_HEIGHT = desktopMode.height;

    constexpr float FREE_FALLING_SPEED_MULTIPLYER = 0.4f;
    constexpr float JUMP_POWER = 0.25f;

    constexpr float KNYAZ_MOVE_SPEED = 600.f;
    const float offset = KNYAZ_MOVE_SPEED * elapsedTime;

    sf::Vector2f knyazPosition = knyaz.body.getPosition();

    if (knyaz.isMovingLeft && knyazPosition.x >= SCREEN_WIDTH / 5 * 2) {
        knyazPosition.x -= offset;
    } else if (knyaz.isMovingLeft && knyazPosition.x < SCREEN_WIDTH / 5 * 2) {
        GameEntity leftEdge = mapObjs[0];
        sf::Vector2f edgeSize = leftEdge.body.getSize();
        sf::Vector2f edgePos = leftEdge.body.getPosition();
        if (edgePos.x + edgeSize.x + offset < 0) {
            for (auto& mapObj : mapObjs) {
                sf::Vector2f entityPos = mapObj.body.getPosition();
                entityPos.x += offset;
                mapObj.body.setPosition(entityPos);
            }
        } else {
            knyazPosition.x -= offset;
        }
    } else if (knyaz.isMovingRight && knyazPosition.x <= SCREEN_WIDTH / 5 * 3) {
        knyazPosition.x += offset;
    } else if (knyaz.isMovingRight && knyazPosition.x > SCREEN_WIDTH / 5 * 3) {
        GameEntity righttEdge = mapObjs[1];
        sf::Vector2f edgePos = righttEdge.body.getPosition();
        if (edgePos.x - offset >= SCREEN_WIDTH) {
            for (auto& mapObj : mapObjs) {
                sf::Vector2f entityPos = mapObj.body.getPosition();
                entityPos.x -= offset;
                mapObj.body.setPosition(entityPos);
            }
        } else {
            knyazPosition.x += offset;
        }
    }

    knyaz.body.setPosition(knyazPosition);

    checkXCollision();

    knyazPosition = knyaz.body.getPosition();

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

    checkYCollision();
}

sf::RectangleShape getKnyazBody() {
    sf::RectangleShape knyazBody({80.f, 80.f});
    knyazBody.setPosition({39.f, 400.f});
    return knyazBody;
}
