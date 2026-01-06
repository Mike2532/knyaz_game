#include "../../../globals/globals.h"
#include "../../../globals/mapObjs/mapObjs.h"
#include "../../knyaz.h"
#include "../globals/mapEnemys/mapEnemys.h"

bool isKnyazVerticalOverlap(GameEntity entity) {
    return knyaz.getRight() > entity.getLeft() && knyaz.getRight() < entity.getRight() || knyaz.getLeft() > entity.getLeft() && knyaz.getLeft() < entity.getRight();
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