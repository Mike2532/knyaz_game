#include "./Enemy/Enemy.h"
#include <iostream>

vector<Enemy> mapEnemys;

struct EnemyParam {
    const sf::Vector2f enemyPos;
    const float LEFT_ACTIVE_EDGE;
    const float LEFT_PATROLING_EDGE;
    const float RIGHT_PATROLING_EDGE;
    const float RIGHT_ACTIVE_EDGE;
    const int id;
    const bool isBoss;
};

auto addEnemy(const EnemyParam &enemyParam) {
    Enemy myEnemy;
    myEnemy.body.setSize({50.f, 60.f});
    myEnemy.body.setPosition(enemyParam.enemyPos);
    myEnemy.LEFT_ACTIVE_EDGE = enemyParam.LEFT_ACTIVE_EDGE;
    myEnemy.LEFT_PATROLING_EDGE = enemyParam.LEFT_PATROLING_EDGE;
    myEnemy.RIGHT_PATROLING_EDGE = enemyParam.RIGHT_PATROLING_EDGE;
    myEnemy.RIGHT_ACTIVE_EDGE = enemyParam.RIGHT_ACTIVE_EDGE;
    myEnemy.animationData = animationContainer["enemyWalk"];
    myEnemy.id = enemyParam.id;
    myEnemy.isBoss = enemyParam.isBoss;

    if (enemyParam.isBoss) {
        myEnemy.body.setSize({120.f, 200.f});
        myEnemy.MAX_HP = 7000;
        myEnemy.hp = 7000;
        myEnemy.X_OFFSET = 37;
        myEnemy.Y_OFFSET = 32;
        myEnemy.ANIMATION_WIDTH = 33;
        myEnemy.ANIMATION_HEIGHT = 28;
        myEnemy.ANIMATION_TEXTURE_SCALE_X = 10.f;
        myEnemy.ANIMATION_TEXTURE_SCALE_Y = 10.f;
        myEnemy.SPRITE_POS_X_OFFSET = -190.f;
        myEnemy.SPRITE_POS_Y_OFFSET = 50.f;
        myEnemy.SPRITE_POS_ADDITIONAL_OFFSET = 260.f;
        myEnemy.attackPower = 650 * 2;
        myEnemy.animationData = animationContainer["bossWalk"];
    }

    mapEnemys.push_back(myEnemy);
}

const vector<EnemyParam> enemyParams {
        { //MW
                {1932.f + 150.f, 691.f + 20.f - 2.f + 100.f},
                1774.f,
                1899.f,
                2290.f,
                2420.f,
                0,
                false
        },
        { //Start 1-st
                {466.f + 150.f, 461.f + 20.f - 2.f + 100.f},
                407.f,
                407.f,
                653.f,
                653.f,
                1,
                false
        },
        { //Start 2-nd
                {702.f + 150.f, 67.f + 20.f - 2.f + 100.f},
                655.f,
                680.f,
                982.f,
                1012.f,
                2,
                false
        },
        {  //Tower 1-st
                {2435.f, 431.f + 20.f - 2.f + 100.f},
                2425.f,
                2425.f,
                2560.f,
                2560.f,
                3,
                false
        },
        { //Tower 2-nd
                {2770.f, 214.f + 20.f - 2.f + 100.f},
                2720.f,
                2720.f,
                2855.f,
                2855.f,
                4,
                false
        },
        { //4zone near 1-st portal
                {3138.f, 676.f + 100.f},
                3000,
                3063,
                3468,
                3538,
                5,
                false
        },
        { //4zone near 4 portal
                {3942.f, 40.f + 100.f},
                3905,
                3905,
                4210 - 70.f,
                4230 - 70.f,
                6,
                false
        },
        { //4zone battle area
                {3892.f, 711.f + 100.f},
                3774,
                3860,
                4250,
                4290,
                7,
                false
        },
        { //4zone dls 1
                {4140.f, 435.f + 100.f},
                3985,
                3995,
                4300,
                4310,
                8,
                false
        },
        { //4zone dls 2
            {3894.f, 556.f + 100.f},
            3774,
            3789,
            4092,
            4107,
            9,
                false
        },
        { //boss arena p1
                {4632.f + 100.f, 467.f + 100.f},
                4571,
                4571,
                4743 + 5,
                4743 + 5,
                10,
                false
        },
        { //boss arena p3
                {5546.f + 100.f, 467.f + 100.f},
                5485,
                5485,
                5657 + 5,
                5657 + 5,
                11,
                false
        },
        { //game boss
                {5206.f, 571.f + 100.f},
                4340,
                4541,
                5574,
                5775,
                -1,
                true
        }
};

void initEnemys() {
    mapEnemys.clear();
    for (auto &enemyParam : enemyParams) {
        addEnemy(enemyParam);
    }
}
