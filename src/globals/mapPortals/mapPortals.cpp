#include "./Portal.h"

using namespace std;

vector<Portal> mapPortals;


struct PortalParam{
    sf::Vector2f inCoords;
    sf::Vector2f outCoords;
    sf::Vector2f inBodySize;
    sf::Vector2f inBodyPos;
    sf::Vector2f outBodySize;
    sf::Vector2f outBodyPos;
};

auto makePortal(PortalParam params) {
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
        }
};

void initMapPortals() {
    mapPortals.clear();

    for (auto& param : portalParams) {
        mapPortals.emplace_back(makePortal(param));
    }
}