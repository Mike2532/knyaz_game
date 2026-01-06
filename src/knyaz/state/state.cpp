#include "../../globals/globals.h"
#include "../../globals/mapPortals/mapPortals.h"
#include "./knyaz.h"
#include "../../globals/tpEntity/tpEntity.h"

using namespace std;

sf::RectangleShape initKnyazBody() {
    constexpr float KNYAZ_X_SIZE = 45.f;
    constexpr float KNYAZ_Y_SIZE = 75.f;
    constexpr float KNYAZ_START_X = 39.f;
    constexpr float KNYAZ_START_Y = 400.f;

    sf::RectangleShape knyazBody({KNYAZ_X_SIZE, KNYAZ_Y_SIZE});
    knyazBody.setPosition({KNYAZ_START_X, KNYAZ_START_Y});
    return knyazBody;
}

void updateHpIndicator() {
    sf::Color HpColor = HpIndicatorSprite.getColor();
    HpColor.a = 255 * float (float (knyaz.MAX_HP - knyaz.hp) / knyaz.MAX_HP);
    HpIndicatorSprite.setColor(HpColor);
}

void checkKnyazPortaling() {
    const sf::Vector2f knyazPos = knyaz.body.getPosition();
    for (int i = 0; i < mapPortals.size(); i++) {
        Portal portal = mapPortals[i];
        const sf::Vector2f portalPos = portal.inCoords;
        if (abs(portalPos.x - knyazPos.x) <= 25 && abs(portalPos.y - knyazPos.y) <= 2 && !knyaz.isTp) {
            spawnTpEntity(knyazPos);
            spawnTpEntity(portal.outCoords);
            knyaz.tpTimer.restart();
            knyaz.isTp = true;
            knyaz.tpCoords = portal.outCoords;
            if (i == mapPortals.size() - 1) {
                lastTeleported = true;
                knyaz.isFlyingUp = false;
            } else if (i == 0) {
                knyaz.isFlyingUp = true;
            }
            break;
        }
    }
}