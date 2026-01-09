#ifndef KNYAZ_GAME_KNYAZRUNFX_H
#define KNYAZ_GAME_KNYAZ_H

#include "../globals/AnimatedObj/AnimatedObj.h"

using namespace std;

enum class jumpStates {base, oneJump, secondJump, heated, falling};

struct Knyaz : AnimatedObj {
    const int MAX_HP = 3000;
//    const int MAX_HP = 300000000;
    const int MAX_FOCUS_COUNTER = 6;
    const int MAX_RAGE_COUNTER = 3;

    jumpStates curJMPState = jumpStates::base;
    int jumpCounter = 0;
    const int MAX_JUMP_COUNTER = 2;

    int lastHeatedEnemy;
    vector<string> actionsHistory;

    bool isMovingLeft = false;
    bool isMovingRight = false;
    bool isJump = false;
    bool isDoubleJump = false;
    bool isClimbing = false;

    bool jmpAccess = true;

    bool isRunning = false;

    bool isAttackFinished = false;
    bool isFlyingUp = false;

    int hp = MAX_HP;
    int lightAttackPower = 400;
    int heavyAttackPower = 700;
    int rageAttackPower = 2200;
    int takenDamage = 0;

    int rageCounter = 0;
    int focusCounter = 0;

    //TODO ПОМЕНЯТЬ
//    bool meetTheBoos = false;
    bool meetTheBoos = true;

    sf::Clock attackTimer;
    sf::Clock damageTimer;
    sf::Clock climbingTimer;

    bool isTp = false;
    sf::Clock tpTimer;
    sf::Vector2f tpCoords;

    void textureUpdate() override;
    void spritePositionUpdate();
    void takeDamage();
    void tpProcess();
};

extern Knyaz knyaz;

#endif //KNYAZ_GAME_KNYAZRUNFX_H
