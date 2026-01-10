#include "./globals/globals.h"
#include "./globals/mapEnemys/mapEnemys.h"

void drawMapEnemys() {
    for (auto &enemy : mapEnemys) {
        window.draw(enemy.objSprite);
    }
}