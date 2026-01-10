#include "../globals/globals.h"
#include "./keyboard/keyboardHandler.h"
#include "./mouse/mouseHandler.h"
#include "../state/state.h"
#include "../../globals/mapObjs/mapObjs.h"
#include "../../globals/mapPortals/mapPortals.h"
#include "../knyaz.h"
#include "../../globals/mapEnemys/mapEnemys.h"
#include "../resources/sounds/fx/run/knyazRunFX.h"
#include "../globals/bottle/bottle.h"

using namespace std;

void movementHandler() {
    if (knyaz.isFlyingUp) {
        return;
    }

    bool moveLeftPressed = sf::Keyboard::isKeyPressed(keymap["MOVE_LEFT_KEY"]);
    bool moveRightPressed = sf::Keyboard::isKeyPressed(keymap["MOVE_RIGHT_KEY"]);
    bool isKnyazStanding = !(knyaz.curJMPState == jumpStates::oneJump || knyaz.curJMPState == jumpStates::secondJump || knyaz.isFalling);

    if (moveLeftPressed || moveRightPressed) {
        knyaz.isAtacking = false;
    }

    if (moveLeftPressed && !knyaz.isMovingLeft) {
        if (knyaz.isClimbing && knyaz.isLeftOrented) {
            return;
        }
        knyaz.isMovingLeft = true;
        if (isKnyazStanding) {
            knyaz.changeAnimation(animationContainer["run"]);
            startKnyazRunSound();
        }
        if (!knyaz.isLeftOrented) knyaz.isLeftOrented = true;
    } else if (!moveLeftPressed && knyaz.isMovingLeft) {
        knyaz.isMovingLeft = false;
        if (!knyaz.isMovingRight && isKnyazStanding) {
            knyaz.changeAnimation(animationContainer["idle"]);
            stopKnyazRunSound();
        }
    } else if (moveRightPressed && !knyaz.isMovingRight) {
        if (knyaz.isClimbing && !knyaz.isLeftOrented) {
            return;
        }
        knyaz.isMovingRight = true;
        if (isKnyazStanding) {
            knyaz.changeAnimation(animationContainer["run"]);
            startKnyazRunSound();
        }
        if (knyaz.isLeftOrented) knyaz.isLeftOrented = false;
    } else if (!moveRightPressed && knyaz.isMovingRight) {
        knyaz.isMovingRight = false;
        if (!knyaz.isMovingLeft && isKnyazStanding) {
            knyaz.changeAnimation(animationContainer["idle"]);
            stopKnyazRunSound();
        }
    }

}

void cameraRespawn() {
    constexpr float LOGIC_W = 1440;
    constexpr float LOGIC_H = 900;

    const float cameraRespawnX = (knyaz.meetTheBoos)
                                 ? LOGIC_W / 2 + LOGIC_W * 3
                                 : LOGIC_W / 2;

    gameView.setCenter({cameraRespawnX, LOGIC_H / 2});
}

void gameRestart() {
    knyaz.body = initKnyazBody();
    initGameMap();
    initEnemys();
    initMapPortals();
    initAntiGravityField();
    lastTeleported = false;

    knyaz.fullHPReset();
    knyaz.battleReset();
    knyaz.stopRun();
    knyaz.animationsReset();

    cameraRespawn();
    spawnBossBottles();

    if (!knyaz.meetTheBoos) {
        return;
    }
    knyazMeetBossProcess();
}

bool isGameShouldRestart(const sf::Event& event) {
   return !knyaz.isAlive && (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed) && knyaz.animationFrameNumber == knyaz.animationData.animationFrames - 1;
}

void knyazEventsHandler(const sf::Event& event) {
    if (knyaz.isAlive && !knyaz.isTp) {
        if (event.type == sf::Event::MouseButtonPressed && !knyaz.isClimbing) {
            mouseEventsHandler(event);
        }

        if (event.type == sf::Event::KeyPressed) {
            keyboardEventsHandler();
        }

        movementHandler();
    } else if (isGameShouldRestart(event)) {
        gameRestart();
    }
}