#include "../../globals/globals.h"
#include "../../globals/mapEnemys/Enemy/Enemy.h"
#include "../../globals/mapEnemys/mapEnemys.h"
#include "algorithm"

using namespace std;

void removeDeathEnemys() {
    auto toRemove = remove_if(mapEnemys.begin(), mapEnemys.end(), [](Enemy &enemy) {
        return
            (!enemy.isBoss && enemy.hp <= 0) ||
            (enemy.hp <= 0 && (enemy.animationData.animationType == AnimationTypes::DEATH && enemy.animationFrameNumber == enemy.animationData.animationFrames - 1));
    });
    mapEnemys.erase(toRemove, mapEnemys.end());
}