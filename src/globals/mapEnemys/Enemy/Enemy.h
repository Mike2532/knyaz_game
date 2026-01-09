#ifndef KNYAZ_GAME_ENEMY_H
#define KNYAZ_GAME_ENEMY_H

#include "../../mapObjs/GameEntity/GameEntity.h"
#include "../../AnimatedObj/AnimatedObj.h"
#include "../../globals.h"

struct Enemy : AnimatedObj {
    int id;
//    int MAX_HP = 2000;
    int MAX_HP = 200000000;
    float STUNNED_TIME = 3.f;

    float LEFT_PATROLING_EDGE;
    float RIGHT_PATROLING_EDGE;
    float LEFT_ACTIVE_EDGE;
    float RIGHT_ACTIVE_EDGE;

    bool isNearLeftKnyaz = false;
    bool isNearRightKnyaz = false;
    bool seeKnyaz = false;
    bool isPatrolingLeft = true;
    bool isAttacking = false;

    sf::Clock stunnedTimer;

    int hp = MAX_HP;
    int attackPower = 650;
    int takenDamage = 0;

    sf::Clock searchingTimer;
    sf::Clock attackTimer;
    EnemyStates state = EnemyStates::PATROLLING;

    bool needToReverse = false;
    sf::Clock reverseTimer;

    void move(const float& elapsedTime);

    void checkKnyazVision();

    bool isAttackingNow(int x);

    void tryToAttack();

    void textureUpdate() override;

    void spritePositionUpdate();

    void stunProcess();

    void easyComboReversal();
};

#endif //KNYAZ_GAME_ENEMY_H
