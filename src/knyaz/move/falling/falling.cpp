#include "../globals/globals.h"
#include "../collisionChecker/checker.h"

void fallingCheck(bool &falling) {
    for (auto entity : mapObjs) {
        if (isKnyazVerticalOverlap(entity) && abs(knyaz.getBot() - entity.getTop()) < 0.2f) {
            falling = false;
            if (knyaz.isAlive && (entity.type == ObjsTypes::OBTACLE || entity.type == ObjsTypes::SPIKES_UP)) {
                knyaz.changeAnimation(animationContainer["death"]);
                knyaz.isAlive = false;
                knyaz.hp = 0;
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
        if (!(knyaz.isMovingRight || knyaz.isMovingLeft)) knyaz.changeAnimation(animationContainer["idle"]);
        else knyaz.changeAnimation(animationContainer["run"]);
    }

    if (falling == knyaz.isFalling) return;
    if (falling && !knyaz.isJump && knyaz.isAlive) knyaz.changeAnimation(animationContainer["falling"]);
    if (falling) {
        knyaz.isFalling = true;
        knyaz.freeFallingTimer.restart();
    } else {
        knyaz.isFalling = false;
        knyaz.isJump = false;
        knyaz.isDoubleJump = false;
    }
}