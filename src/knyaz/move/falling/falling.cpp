#include "../globals/globals.h"
#include "../collisionChecker/checker.h"
#include "../../../globals/mapObjs/mapObjs.h"
#include "../../knyaz.h"
#include "../resources/sounds/fx/landing/knyazLandingFX.h"
#include "../resources/sounds/fx/fight/fight.h"
#include "../resources/sounds/fx/wind/wind.h"

void fallingCheck(bool &falling) {
    for (auto entity : mapObjs) {
        if (isKnyazVerticalOverlap(entity) && abs(knyaz.getBot() - entity.getTop()) < 0.2f) {
            falling = false;
            if (knyaz.isAlive && (entity.type == ObjsTypes::OBTACLE || entity.type == ObjsTypes::SPIKES_UP)) {
                knyaz.changeAnimation(animationContainer["death"]);
                knyaz.isAlive = false;
                knyaz.hp = 0;
                cout << "AAAA\n";
                playRandomFlashSound();
                stopWindSound();
            }
            break;
        }
    }
}

void checkKnyazFalling() {
    bool falling = true;
    fallingCheck(falling);

    if (knyaz.isClimbing) return;

    if (knyaz.isFalling && !falling) {
        if (!(knyaz.isMovingRight || knyaz.isMovingLeft)) {
            knyaz.changeAnimation(animationContainer["idle"]);
            playRandomLandingSound();
            stopWindSound();
        } else {
            knyaz.changeAnimation(animationContainer["run"]);
            playRandomLandingSound();
            stopWindSound();
        }
    }

    if (falling == knyaz.isFalling) return;
    if (falling && !knyaz.isJump && knyaz.isAlive) knyaz.changeAnimation(animationContainer["falling"]);
    if (falling) {
        knyaz.isFalling = true;
        knyaz.freeFallingTimer.restart();
        playRandomWindSound();
    } else {
        knyaz.isFalling = false;
        knyaz.isJump = false;
        knyaz.isDoubleJump = false;
        stopWindSound();
    }

}