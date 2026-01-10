#ifndef KNYAZ_GAME_KNYAZRUNFX_H
#define KNYAZ_GAME_KNYAZ_H

#include "../globals/AnimatedObj/AnimatedObj.h"

using namespace std;

enum class jumpStates {base, oneJump, secondJump, falling};

struct Knyaz : AnimatedObj {
    const int MAX_HP = 4000;
    const int MAX_FOCUS_COUNTER = 6;
    const int MAX_RAGE_COUNTER = 3;
    const int MAX_JUMP_COUNTER = 2;

    vector<string> actionsHistory;
    jumpStates curJMPState = jumpStates::base;
    sf::Clock attackTimer;
    sf::Clock damageTimer;
    sf::Clock climbingTimer;
    sf::Clock tpTimer;
    sf::Vector2f tpCoords;

    int jumpCounter = 0;
    int lastHeatedEnemy;
    int hp = MAX_HP;
    int lightAttackPower = 400;
    int heavyAttackPower = 700;
    int rageAttackPower = 2200;
    int takenDamage = 0;
    int rageCounter = 0;
    int focusCounter = 0;

    bool isMovingLeft = false;
    bool isMovingRight = false;
    bool isClimbing = false;
    bool isAtacking = false;
    bool isAttackFinished = true;
    bool isFlyingUp = false;
//    bool meetTheBoos = false;
    bool meetTheBoos = true;
    bool isTp = false;

    void textureUpdate() override;
    void spritePositionUpdate();
    void takeDamage();
    void tpProcess();
    void stopRun();
    void dieProcess();
    void battleReset();
    void fullHPReset();
    void animationsReset();
};

extern Knyaz knyaz;

#endif //KNYAZ_GAME_KNYAZRUNFX_H
