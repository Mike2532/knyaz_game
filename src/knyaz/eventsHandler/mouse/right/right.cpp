#include <SFML/Window/Event.hpp>
#include "../globals/globals.h"
#include "../../../knyaz.h"
#include "../globals/mapEnemys/mapEnemys.h"
#include "../resources/sounds/fx/rage/rage.h"

bool stunComboChecker(const vector<string>& ah) {
    return ah.size() == 2 && ah[0] == "ea" && ah[1] == "jmp";
}

void stunComboProcess(Enemy& enemy) {
    knyaz.actionsHistory.clear();
    enemy.stunnedTimer.restart();
    enemy.isStunned = true;
    playRageSound();
}

bool focusComboChecker(const vector<string>& ah) {
    return ah.size() == 1 && ah[0] == "ea";
}

void focusComboProcess() {
    knyaz.actionsHistory.emplace_back("ha");
}

void heavyComboChecker(Enemy& enemy) {
    if (stunComboChecker(knyaz.actionsHistory)) {
        stunComboProcess(enemy);
    } else if (focusComboChecker(knyaz.actionsHistory)) {
        focusComboProcess();
    }
}

bool isHeavyAttackAvaliable(const Enemy& enemy) {
    return (enemy.isNearLeftKnyaz  && !knyaz.isLeftOrented) || (enemy.isNearRightKnyaz &&  knyaz.isLeftOrented);
}

void heavyAttackProcess(Enemy& enemy, const int& DAMAGE_OFFSET) {
    sf::Vector2f enemyPos = enemy.body.getPosition();
    enemyPos.x += knyaz.isLeftOrented ? -DAMAGE_OFFSET : DAMAGE_OFFSET;
    enemy.body.setPosition(enemyPos);

    enemy.takenDamage += knyaz.heavyAttackPower;
    enemy.objSprite.setColor(sf::Color::Red);
    knyaz.attackTimer.restart();
}

void lastHeatedProcess(const Enemy& enemy) {
    if (enemy.id != knyaz.lastHeatedEnemy) {
        knyaz.actionsHistory.clear();
    }
}

void rightMouseHandler(const int& DAMAGE_OFFSET) {
    knyaz.changeAnimation(animationContainer["heavyAttack"]);
    for (auto &enemy : mapEnemys) {
        if (!isHeavyAttackAvaliable(enemy)) {
            continue;
        }

        lastHeatedProcess(enemy);
        heavyComboChecker(enemy);
        heavyAttackProcess(enemy, DAMAGE_OFFSET);
    }
}