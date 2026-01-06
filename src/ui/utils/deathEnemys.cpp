#include "../../globals/globals.h"
#include "../../globals/mapEnemys/Enemy/Enemy.h"
#include "../../globals/mapEnemys/mapEnemys.h"
#include "algorithm"

using namespace std;

void removeDeathEnemys() {
    auto toRemove = remove_if(mapEnemys.begin(), mapEnemys.end(), [](Enemy &enemy) {return enemy.hp <= 0;});
    mapEnemys.erase(toRemove, mapEnemys.end());
}