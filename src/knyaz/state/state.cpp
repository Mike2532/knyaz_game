#include "../../globals/globals.h"
#include "../../globals/mapPortals/mapPortals.h"
#include "./knyaz.h"
#include "../../globals/tpEntity/tpEntity.h"
#include "../resources/sounds/fx/tp/tp.h"
#include "../globals/mapObjs/mapObjs.h"
#include "../resources/sounds/fx/wind/wind.h"
#include "../resources/BG/BG.h"
#include "../knyaz/eventsHandler/eventsHandler.h"

using namespace std;

sf::RectangleShape initKnyazBody() {
    constexpr float KNYAZ_X_SIZE = 45.f;
    constexpr float KNYAZ_Y_SIZE = 75.f;
    constexpr float KNYAZ_START_X = 39.f;
    constexpr float KNYAZ_START_Y = 400.f + 100.f;

    const float knyazSpawnX = (knyaz.meetTheBoos)
            ? KNYAZ_START_X + 1440 * 3
            : KNYAZ_START_X;

    sf::RectangleShape knyazBody({KNYAZ_X_SIZE, KNYAZ_Y_SIZE});
    knyazBody.setPosition({knyazSpawnX, KNYAZ_START_Y});
    return knyazBody;
}

void updateHpIndicator() {
    sf::Color HpColor = HpIndicatorSprite.getColor();
    HpColor.a = 255 * float (float (knyaz.MAX_HP - knyaz.hp) / knyaz.MAX_HP);
    HpIndicatorSprite.setColor(HpColor);
}

void knyazMeetBossProcess() {
    const auto prevLeftEdge = mapObjs[0];
    const auto prevRightEdge = mapObjs[1];
    const auto newRightEdge = mapObjs[2];
    mapObjs[0] = prevRightEdge;
    mapObjs[1] = newRightEdge;
    mapObjs[2] = prevLeftEdge;
}

void checkKnyazPortaling() {
    const sf::Vector2f knyazPos = knyaz.body.getPosition();
    for (int i = 0; i < mapPortals.size(); i++) {
        Portal portal = mapPortals[i];
        const sf::Vector2f portalPos = portal.inCoords;
        if (abs(portalPos.x - knyazPos.x) <= 25 && abs(portalPos.y - knyazPos.y) <= 2 && !knyaz.isTp) {
            playTpSound();
            spawnTpEntity(knyazPos);
            spawnTpEntity(portal.outCoords);
            knyaz.tpTimer.restart();
            knyaz.isTp = true;
            knyaz.tpCoords = portal.outCoords;
            knyaz.stopRun();
            if (i == 1) {
                teleportedToZone4 = true;
                knyaz.isFlyingUp = false;
            } else if (i == 0) {
                knyaz.isFlyingUp = true;
            } else if (i == 2) {
                teleportedToBoss = true;
                knyaz.meetTheBoos = true;
                knyazMeetBossProcess();
            } else if (i == 3) {
                knyaz.meetTheBoos = false;
                knyaz.body = initKnyazBody();
                curState = GameState::GAME_END;
                teleportedToBoss = false;
                teleportedToZone4 = false;
                gameRestart();
                updateBGSprite();
                stopWindSound();
            }
            break;
        }
    }
}