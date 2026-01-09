#include <SFML/System/Vector2.hpp>
#include "./bossType.h"


void initBoss() {
    const sf::Vector2f BOSS_SIZE{120.f, 200.f};
    const sf::Vector2f BOSS_POS{5206.f, 571.f + 100.f};
    const pair<float, float> BOSS_PATROLING_AREA {4541.f, 5574.f};
    const pair<float, float> BOSS_ACTIVE_AREA {4340.f, 5775.f};
    const int BOSS_ID = -1;

    boss.body.setSize(BOSS_SIZE);
    boss.body.setPosition(BOSS_POS);
    boss.LEFT_ACTIVE_EDGE = BOSS_ACTIVE_AREA.first;
    boss.LEFT_PATROLING_EDGE = BOSS_PATROLING_AREA.first;
    boss.RIGHT_PATROLING_EDGE = BOSS_PATROLING_AREA.second;
    boss.RIGHT_ACTIVE_EDGE = BOSS_ACTIVE_AREA.second;
    boss.animationData = animationContainer["bossWalk"];
    boss.id = BOSS_ID;
    boss.isBoss = true;

    boss.MAX_HP = 10000;
    boss.X_OFFSET = 37;
    boss.Y_OFFSET = 32;
    boss.ANIMATION_WIDTH = 33;
    boss.ANIMATION_HEIGHT = 28;
    boss.ANIMATION_TEXTURE_SCALE_X = 10.f;
    boss.ANIMATION_TEXTURE_SCALE_Y = 10.f;
    boss.SPRITE_POS_X_OFFSET = -190.f;
    boss.SPRITE_POS_Y_OFFSET = 50.f;
    boss.SPRITE_POS_ADDITIONAL_OFFSET = 260.f;
    boss.attackPower = 650 * 2;
}