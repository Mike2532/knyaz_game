#include "../globals/globals.h"
#include "../globals/mapPortals/mapPortals.h"
#include "../globals/tpEntity/tpEntity.h"

void drawPortals() {
    if (!lastTeleported) {
        window.draw(antiGravityField);
        for (int i = 0; i < 2; i++) {
            window.draw(mapPortals[i].inBody);
            window.draw(mapPortals[i].outBody);
        }
    }

    if (!superLastTeleported) {
        window.draw(mapPortals[2].inBody);
        window.draw(mapPortals[2].outBody);
    }

    if (mapPortals.size() == 4) {
        window.draw(mapPortals[3].inBody);
    }

    for (auto& e : tpEntityArr) {
        window.draw(e.objSprite);
        e.animationProcess();
    }

}