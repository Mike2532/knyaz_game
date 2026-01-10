#include "./globals/globals.h"
#include "./globals/mapEnemys/mapEnemys.h"
#include "../knyaz/knyaz.h"
#include "../knyaz/state/state.h"
#include "../knyaz/move/falling/falling.h"
#include "../knyaz/move/move.h"
#include "../knyaz/move/collisionChecker/checker.h"
#include "../globals/mapEnemys/enemysDamage.h"
#include "../ui/utils/deathEnemys.h"
#include "./resources/ui/ui.h"


void updateGame() {
    float elapsedTime = globalTimer.getElapsedTime().asSeconds();
    globalTimer.restart();

    for (auto &enemy : mapEnemys) {
        enemy.stunProcess();
        enemy.checkKnyazVision();
        enemy.move(elapsedTime);
        enemy.tryToAttack();
        enemy.animationProcess();
        enemy.spritePositionUpdate();
        enemy.easyComboReversal();
    }

    checkKnyazPortaling();
    checkKnyazFalling();
    knyazMove(elapsedTime);
    checkKnyazEnemyCollision();
    enemysTakenDamage();
    removeDeathEnemys();
    knyaz.animationProcess();
    knyaz.spritePositionUpdate();
    knyaz.takeDamage();
    knyaz.tpProcess();
    updateHpIndicator();
    updateUI();
}