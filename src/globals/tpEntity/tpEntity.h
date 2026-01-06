#ifndef KNYAZ_GAME_TPENTITY_H
#define KNYAZ_GAME_TPENTITY_H

#include "../AnimatedObj/AnimatedObj.h"

using namespace std;

struct TpEntity : AnimatedObj {
    void textureUpdate() override;
};

extern vector<TpEntity> tpEntityArr;
void spawnTpEntity(const sf::Vector2f knyazPos);

#endif //KNYAZ_GAME_TPENTITY_H
