#include "./Portal.h"
#include "./PortalParam.h"

using namespace std;

vector<Portal> mapPortals;

Portal makePortal(PortalParam params) {
    Portal portal;
    portal.inCoords = params.inCoords;
    portal.outCoords = params.outCoords;

    sf::RectangleShape inBody;
    inBody.setSize(params.inBodySize);
    inBody.setPosition(params.inBodyPos);
    inBody.setFillColor(sf::Color::Blue);
    portal.inBody = inBody;

    sf::RectangleShape outBody;
    outBody.setSize(params.outBodySize);
    outBody.setPosition(params.outBodyPos);
    outBody.setFillColor(sf::Color::Red);
    portal.outBody = outBody;

    return portal;
}

vector<PortalParam> portalParams {
        {
                {3498.f + 20.f, 661.f + 100.f},
                {3661.f - 60.f, 661.f + 100.f},
                {5.f, 100.f},
                {3543.f, 636.f + 100.f},
                {100.f, 5.f},
                {3634.f, 736.f + 100.f}
        },
        {
                {3661.f, 35.f + 100.f},
                {4190.f - 60.f, 25.f + 100.f},
                {100.f, 5.f},
                {3634.f, 30.f + 100.f},
                {5.f, 100.f},
                {4235.f - 60.f, 0.f + 100.f}
        },
        {
                {4315.f - 27.f, 671.f + 125.f},
                {4340.f + 45.f, 671.f + 110.f},
                {5.f, 100.f},
                {4315.f - 10.f, 671.f + 100.f},
                {5.f, 100.f},
                {4340.f, 671.f + 100.f}
        }
};

void initMapPortals() {
    mapPortals.clear();

    for (auto& param : portalParams) {
        mapPortals.emplace_back(makePortal(param));
    }
}