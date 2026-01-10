#include "./globals/globals.h"
#include "../knyaz/knyaz.h"
#include "../UI/DrawerUI.h"
#include "../MapObjs/DrawerMapObjs.h"
#include "../MapEnemys/DrawerMapEnemys.h"
#include "../Porals/DrawerPortals.h"

void drawGame() {
    window.setView(gameView);
    window.draw(knyaz.objSprite);

    drawMapEnemys();
    drawMapObjs();

    drawPortals();
    drawUI();
}