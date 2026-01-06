#ifndef KNYAZ_GAME_KNYAZ_H
#define KNYAZ_GAME_KNYAZ_H

#include "../globals/AnimatedObj/AnimatedObj.h"

using namespace std;

struct Knyaz : AnimatedObj {
    const int MAX_HP = 3000;
    const int MAX_FOCUS_COUNTER = 6;
    const int MAX_RAGE_COUNTER = 3;

    int lastHeatedEnemy;
    vector<string> actionsHistory;

    bool isMovingLeft = false;
    bool isMovingRight = false;
    bool isJump = false;
    bool isDoubleJump = false;
    bool isClimbing = false;

    bool isAttackFinished = false;
    bool isFlyingUp = false;

    int hp = MAX_HP;
    int lightAttackPower = 400;
    int heavyAttackPower = 700;
    int rageAttackPower = 2200;
    int takenDamage = 0;

    int rageCounter = 0;
    int focusCounter = 0;

    sf::Clock attackTimer;
    sf::Clock damageTimer;
    sf::Clock climbingTimer;

    void textureUpdate() override;

    void spritePositionUpdate();

    void takeDamage();
};

extern Knyaz knyaz;

#endif //KNYAZ_GAME_KNYAZ_H
