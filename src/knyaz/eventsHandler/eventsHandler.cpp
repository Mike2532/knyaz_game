#include "../globals/globals.h"
#include "./keyboard/keyboardHandler.h"
#include "./mouse/mouseHandler.h"
#include "../state/state.h"

using namespace std;

void movementHandler() {
    bool moveLeftPressed = sf::Keyboard::isKeyPressed(keymap["MOVE_LEFT_KEY"]);
    bool moveRightPressed = sf::Keyboard::isKeyPressed(keymap["MOVE_RIGHT_KEY"]);
    bool isKnyazStanding = !(knyaz.isJump || knyaz.isFalling);
    if (moveLeftPressed && !knyaz.isMovingLeft) {
        if (knyaz.isClimbing && knyaz.isLeftOrented) {
            return;
        }
        knyaz.isMovingLeft = true;
        if (isKnyazStanding) knyaz.changeAnimation(animationContainer["run"]);
        if (!knyaz.isLeftOrented) knyaz.isLeftOrented = true;
    } else if (!moveLeftPressed && knyaz.isMovingLeft) {
        knyaz.isMovingLeft = false;
        if (!knyaz.isMovingRight && isKnyazStanding) knyaz.changeAnimation(animationContainer["idle"]);
    } else if (moveRightPressed && !knyaz.isMovingRight) {
        if (knyaz.isClimbing && !knyaz.isLeftOrented) {
            return;
        }
        knyaz.isMovingRight = true;
        if (isKnyazStanding) knyaz.changeAnimation(animationContainer["run"]);
        if (knyaz.isLeftOrented) knyaz.isLeftOrented = false;
    } else if (!moveRightPressed && knyaz.isMovingRight) {
        knyaz.isMovingRight = false;
        if (!knyaz.isMovingLeft && isKnyazStanding) knyaz.changeAnimation(animationContainer["idle"]);
    }

}

void gameRestart() {
    knyaz.body = initKnyazBody();
    initGameMap();
    initEnemys();
    initMapPortals();
    initAntiGravityField();
    knyaz.isAlive = true;
    knyaz.hp = knyaz.MAX_HP;
    knyaz.focusCounter = 0;
    knyaz.rageCounter = 0;
    knyaz.changeAnimation(animationContainer["falling"]);
    knyaz.freeFallingTimer.restart();
}

bool isGameShouldRestart(const sf::Event& event) {
   return !knyaz.isAlive && (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed) && knyaz.animationFrameNumber == knyaz.animationData.animationFrames - 1;
}

void knyazEventsHandler(const sf::Event& event) {
    if (knyaz.isAlive) {
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