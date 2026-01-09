#include "./mapPortals.h"

PortalParam gameEndPortalParam {
        {5755.f - 40.f, 571.f + 100.f},
        {5775.f - 60.f, -500.f},
        {5.f, 80.f},
        {5755.f, 571.f + 100.f},
        {5.f, 100.f},
        {5775.f - 60.f, -500.f},
};

void spawnGameEndPortal() {
    mapPortals.emplace_back(makePortal(gameEndPortalParam));
}