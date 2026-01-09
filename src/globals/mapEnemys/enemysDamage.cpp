#include "../../knyaz/knyaz.h";
#include "./Enemy/Enemy.h"
#include "../mapEnemys/mapEnemys.h"
#include "../../resources/sounds/fx/win/win.h"
#include "../../resources/sounds/fx/fight/fight.h"
#include "../globals/bottle/bottle.h"

void deadBossProcess(const Enemy& enemy) {
    if (!enemy.isBoss) {
        return;
    }
    startKnyazWinSound();
}

void deadEnemyProcess(const Enemy& enemy) {
    int chanse = getBottleSpawnChanse();
    int r2 = rand() % 100;
    if (r2 > chanse) {
        return;
    }

    sf::Vector2f pos = enemy.body.getPosition();
    sf::Vector2f size = enemy.body.getSize();

    float bottleXPos = pos.x + (size.x/2);
    float bottleYPos = pos.y + (size.y);

    spawnBottle({bottleXPos, bottleYPos});
}

void playEnemyHeatSound(const Enemy& enemy) {
    if (enemy.isBoss) {
        playRandomArmorSound();
    } else {
        playRandomFlashSound();
    }
}

void enemyTakeDamage(Enemy& enemy) {
    enemy.hp -= enemy.takenDamage;
    enemy.takenDamage = 0;
    enemy.objSprite.setColor(sf::Color::White);
}

bool isEnemyAlive(const Enemy& enemy) {
    return enemy.hp > 0;
}

bool hasEnemyDamage(const Enemy& enemy) {
    return enemy.takenDamage != 0;
}

void updateKnyazFocus() {
    knyaz.focusCounter = min(knyaz.focusCounter + 1, knyaz.MAX_FOCUS_COUNTER);
}

bool canEnemysTakeDamage() {
    constexpr int ATTACK_DELAY = 100;
    return knyaz.attackTimer.getElapsedTime().asMilliseconds() >= ATTACK_DELAY && knyaz.isAttackFinished;
}

void enemysTakenDamage() {
    if (!canEnemysTakeDamage()) {
        return;
    }

    for (auto &enemy : mapEnemys) {
        if (!hasEnemyDamage(enemy)) {
            continue;
        }
        enemyTakeDamage(enemy);
        playEnemyHeatSound(enemy);
        updateKnyazFocus();

        if (isEnemyAlive(enemy)) {
            return;
        }
        deadBossProcess(enemy);
        deadEnemyProcess(enemy);
    }
    knyaz.isAttackFinished = false;
}