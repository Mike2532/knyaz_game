#include <SFML/Window/Event.hpp>
#include "../globals/globals.h"
#include "../globals/mapEnemys/Enemy/Enemy.h"
#include "../globals/mapEnemys/mapEnemys.h"
#include "../../../knyaz.h"
#include "../resources/sounds/fx/fight/fight.h"
#include "../resources/sounds/fx/tp/tp.h"

bool isLeftEasy(const Enemy& enemy) {
    return enemy.isNearLeftKnyaz && !knyaz.isLeftOrented;
}

bool isRightEasy(const Enemy& enemy) {
    return enemy.isNearRightKnyaz && knyaz.isLeftOrented;
}

bool isCombo(const Enemy& enemy, const Knyaz& knyaz) {
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

void comboProcess(bool isLeft, Enemy& enemy, const sf::Vector2f& enemyPos) {
    sf::Vector2f enymeSize = enemy.body.getSize();
    sf::Vector2f knyazPos = knyaz.body.getPosition();
    sf::Vector2f knyazSize = knyaz.body.getSize();

    knyazPos.x = (isLeft)
            ? enemyPos.x + enymeSize.x
            : enemyPos.x - knyazSize.x;

    knyaz.body.setPosition(knyazPos);
    knyaz.isLeftOrented = !knyaz.isLeftOrented;
    knyaz.actionsHistory.clear();
    playTpSound();
    enemy.needToReverse = true;
    enemy.reverseTimer.restart();
    enemy.changeAnimation(animationContainer["enemyWalk"]);
    enemy.takenDamage += knyaz.lightAttackPower * 0.5;
}

void leftMouseHandler(const int& DAMAGE_OFFSET) {
    knyaz.changeAnimation(animationContainer["easyAttack"]);
    for (auto &enemy : mapEnemys) {
        bool isLeft = isLeftEasy(enemy);
        bool isRight = isRightEasy(enemy);

        if (isLeft || isRight) {
            sf::Vector2f enemyPos = enemy.body.getPosition();
            if (isCombo(enemy, knyaz)) {

                if (isLeft) {
                    comboProcess(true, enemy, enemyPos);
                } else if (isRight) {
                    comboProcess(false, enemy, enemyPos);
                }

            } else {
                falledComboProcess(enemy);
            }
            attackProcess(enemy, enemyPos, DAMAGE_OFFSET);
        }
    }
}