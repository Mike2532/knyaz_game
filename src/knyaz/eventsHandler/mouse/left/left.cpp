#include <SFML/Window/Event.hpp>
#include "../globals/globals.h"

bool isLeftEasy(const Enemy& enemy) {
    return enemy.isNearLeftKnyaz && !knyaz.isLeftOrented;
}

bool isRightEasy(const Enemy& enemy) {
    return enemy.isNearRightKnyaz && knyaz.isLeftOrented;
}

bool isCombo(const Enemy& enemy) {
    return knyaz.actionsHistory.size() == 2 &&
           knyaz.actionsHistory[0] == "ea" &&
           knyaz.actionsHistory[1] == "ha" &&
           knyaz.lastHeatedEnemy == enemy.id;
}

void falledComboProcess(const Enemy& enemy) {
    knyaz.actionsHistory.clear();
    knyaz.lastHeatedEnemy = enemy.id;
    knyaz.actionsHistory.emplace_back("ea");
}

void attackProcess(Enemy& enemy, sf::Vector2f enemyPos, const int& DAMAGE_OFFSET)  {
    enemyPos.x -= DAMAGE_OFFSET;
    enemy.body.setPosition(enemyPos);
    enemy.takenDamage += knyaz.lightAttackPower;
    enemy.objSprite.setColor(sf::Color::Red);
    knyaz.attackTimer.restart();
}

void commonComboProcess(Enemy& enemy) {
    knyaz.actionsHistory.clear();
    enemy.takenDamage += knyaz.lightAttackPower * 0.5;
}

void leftComboProcess(const Enemy& enemy, const sf::Vector2f enemyPos) {
    sf::Vector2f enymeSize = enemy.body.getSize();
    sf::Vector2f knyazPos = knyaz.body.getPosition();
    knyazPos.x = enemyPos.x + enymeSize.x;
    knyaz.body.setPosition(knyazPos);
    knyaz.isLeftOrented = true;
}

void rightComboProcess(const Enemy& enemy, const sf::Vector2f enemyPos) {
    sf::Vector2f knyazSize = knyaz.body.getSize();
    sf::Vector2f knyazPos = knyaz.body.getPosition();
    knyazPos.x = enemyPos.x - knyazSize.x;
    knyaz.body.setPosition(knyazPos);
    knyaz.isLeftOrented = false;
}

void leftMouseHandler(const int& DAMAGE_OFFSET) {
    knyaz.changeAnimation(animationContainer["easyAttack"]);
    for (auto &enemy : mapEnemys) {
        bool isLeft = isLeftEasy(enemy);
        bool isRight = isRightEasy(enemy);

        if (isLeft || isRight) {
            sf::Vector2f enemyPos = enemy.body.getPosition();
            if (isCombo(enemy)) {
                if (isLeft) {
                    leftComboProcess(enemy, enemyPos);
                } else {
                    rightComboProcess(enemy, enemyPos);
                }
                commonComboProcess(enemy);
            } else {
                falledComboProcess(enemy);
            }
            attackProcess(enemy, enemyPos, DAMAGE_OFFSET);
        }
    }
}