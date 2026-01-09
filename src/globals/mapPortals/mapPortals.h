#ifndef KNYAZ_GAME_MAPPORTALS_H
#define KNYAZ_GAME_MAPPORTALS_H

#include "./Portal.h"
#include "./PortalParam.h"

using namespace std;

extern vector<Portal> mapPortals;

Portal makePortal(PortalParam params);
void initMapPortals();

#endif //KNYAZ_GAME_MAPPORTALS_H
