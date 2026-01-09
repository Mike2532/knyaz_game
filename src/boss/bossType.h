#ifndef KNYAZ_GAME_BOSSTYPE_H
#define KNYAZ_GAME_BOSSTYPE_H

#include "../globals/mapEnemys/Enemy/Enemy.h"

struct Boss : Enemy {
    int MAX_HP = 10000;

    int FRAME_WIDTH = 100;
    int X_OFFSET = 37;
    int Y_OFFSET = 32;
    int ANIMATION_WIDTH = 33;
    int ANIMATION_HEIGHT = 28;
    float ANIMATION_TEXTURE_SCALE_X = 10.f;
    float ANIMATION_TEXTURE_SCALE_Y = 10.f;

    float SPRITE_POS_X_OFFSET = -190.f;
    float SPRITE_POS_Y_OFFSET = 50.f;
    float SPRITE_POS_ADDITIONAL_OFFSET = 260.f;
};

extern Enemy boss;

#endif //KNYAZ_GAME_BOSS_H
