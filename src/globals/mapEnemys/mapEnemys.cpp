#include "./Enemy/Enemy.h"
#include "../../knyaz/knyaz.h"
#include "../globals/bottle/bottle.h"
#include <iostream>
#include "../resources/sounds/fx/fight/fight.h"

vector<Enemy> mapEnemys;

struct EnemyParam {
    const sf::Vector2f enemyPos;
    const float LEFT_ACTIVE_EDGE;
    const float LEFT_PATROLING_EDGE;
    const float RIGHT_PATROLING_EDGE;
    const float RIGHT_ACTIVE_EDGE;
    const int id;
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
    mapEnemys.push_back(myEnemy);
}

const vector<EnemyParam> enemyParams {
        { //MW
                {1932.f, 691.f + 20.f - 2.f + 100.f},
                1774.f,
                1899.f,
                2290.f,
                2420.f,
                0
        },
        { //Start 1-st
                {466.f, 461.f + 20.f - 2.f + 100.f},
                407.f,
                407.f,
                653.f,
                653.f,
                1
        },
        { //Start 2-nd
                {702.f, 67.f + 20.f - 2.f + 100.f},
                655.f,
                680.f,
                982.f,
                1012.f,
                2
        },
        {  //Tower 1-st
                {2435.f, 431.f + 20.f - 2.f + 100.f},
                2425.f,
                2425.f,
                2560.f,
                2560.f,
                3
        },
        { //Tower 2-nd
                {2770.f, 214.f + 20.f - 2.f + 100.f},
                2720.f,
                2720.f,
                2855.f,
                2855.f,
                4
        },
        { //4zone near 1-st portal
                {3138.f, 676.f + 100.f},
                3000,
                3063,
                3468,
                3538,
                5
        },
        { //4zone near 4 portal
                {3942.f, 40.f + 100.f},
                3905,
                3905,
                4210,
                4230,
                6
        },
        { //4zone battle area
                {3892.f, 711.f + 100.f},
                3774,
                3860,
                4250,
                4315,
                7
        },
        { //4zone dls 1
                {4140.f, 435.f + 100.f},
                3985,
                3995,
                4300,
                4310,
                8
        },
        { //4zone dls 2
            {3894.f, 556.f + 100.f},
            3774,
            3789,
            4092,
            4107,
            9
        }
};

void initEnemys() {
    mapEnemys.clear();
    for (auto &enemyParam : enemyParams) {
        addEnemy(enemyParam);
    }
}

void enemysTakenDamage() {
    constexpr int ATTACK_DELAY = 100;

    if (knyaz.attackTimer.getElapsedTime().asMilliseconds() >= ATTACK_DELAY && knyaz.isAttackFinished) {
        for (auto &enemy : mapEnemys) {
            if (enemy.takenDamage != 0) {
                playRandomFlashSound();
                knyaz.focusCounter = min(knyaz.focusCounter + 1, knyaz.MAX_FOCUS_COUNTER);
                enemy.hp -= enemy.takenDamage;
                enemy.takenDamage = 0;
                enemy.objSprite.setColor(sf::Color::White);
                if (enemy.hp <= 0) {
                    int chanse = getBottleSpawnChanse();
                    int r2 = rand() % 100;
                    if (r2 <= chanse) {
                        sf::Vector2f pos = enemy.body.getPosition();
                        sf::Vector2f size = enemy.body.getSize();

                        float bottleXPos = pos.x + (size.x/2);
                        float bottleYPos = pos.y + (size.y);

                        spawnBottle({bottleXPos, bottleYPos});
                    }
                }
            }
        }
        knyaz.isAttackFinished = false;
    }
}