#include "./Portal.h"
#include "../globals/viewport/viewport.h"

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
    portal.inCoords = {params.inCoords.x * VIEW_SCALE_X, params.inCoords.y * VIEW_SCALE_Y};
    portal.outCoords = {params.outCoords.x * VIEW_SCALE_X, params.outCoords.y * VIEW_SCALE_Y};;

    sf::RectangleShape inBody;
    inBody.setSize({params.inBodySize.x * VIEW_SCALE_X, params.inBodySize.y * VIEW_SCALE_Y});
    inBody.setPosition({params.inBodyPos.x * VIEW_SCALE_X, params.inBodyPos.y * VIEW_SCALE_Y});
    inBody.setFillColor(sf::Color::Blue);
    portal.inBody = inBody;

    sf::RectangleShape outBody;
    outBody.setSize({params.outBodySize.x * VIEW_SCALE_X, params.outBodySize.y * VIEW_SCALE_Y});
    outBody.setPosition({params.outBodyPos.x * VIEW_SCALE_X, params.outBodyPos.y * VIEW_SCALE_Y});
    outBody.setFillColor(sf::Color::Red);
    portal.outBody = outBody;

    return portal;
}

vector<PortalParam> portalParams {
        {
                {3498.f + 20.f, 661.f},
                {3661.f, 661.f},
                {5.f, 100.f},
                {3543.f, 636.f},
                {100.f, 5.f},
                {3634.f, 736.f}
        },
        {
                {3661.f, 35.f},
                {4190.f, 25.f},
                {100.f, 5.f},
                {3634.f, 30.f},
                {5.f, 100.f},
                {4235.f, 0.f}
        }
};

void initMapPortals() {
    mapPortals.clear();

    for (auto& param : portalParams) {
        mapPortals.emplace_back(makePortal(param));
    }
}