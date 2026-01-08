#ifndef KNYAZ_GAME_MAPOBJS_H
#define KNYAZ_GAME_MAPOBJS_H

#include "./gameEntity/gameEntity.h"

using namespace std;

extern vector<GameEntity> mapObjs;

void initGameMap(const pair<const float, const float>& VIEW_SCALE);

#endif //KNYAZ_GAME_MAPOBJS_H
