#ifndef KNYAZ_GAME_ENEMY_H
#define KNYAZ_GAME_ENEMY_H

#include "../../mapObjs/GameEntity/GameEntity.h"
#include "../../AnimatedObj/AnimatedObj.h"
#include "../../globals.h"

struct Enemy : AnimatedObj {
    bool isBoss = false;

    int id;
    int MAX_HP = 2000;
//    int MAX_HP = 200000000;
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

    int FRAME_WIDTH = 100;
    int X_OFFSET = 34;
    int Y_OFFSET = 31;
    int ANIMATION_WIDTH = 42;
    int ANIMATION_HEIGHT = 31;
    float ANIMATION_TEXTURE_SCALE_X = 4.f;
    float ANIMATION_TEXTURE_SCALE_Y = 4.f;

    float SPRITE_POS_X_OFFSET = 40.f;
    float SPRITE_POS_Y_OFFSET = 40.f;
    float SPRITE_POS_ADDITIONAL_OFFSET = 130.f;

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
