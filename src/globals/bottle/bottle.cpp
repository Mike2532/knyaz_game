#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../mapObjs/mapObjs.h"
#include "../mapObjs/gameEntity/gameEntity.h"
#include "../../resources/objs/objs.h"
#include "../knyaz/knyaz.h"
#include "../mapObjs/GameEntity/GameEntity.h"

using namespace std;

int getBottleSpawnChanse() {
    int knyazHpPercent = float(float (knyaz.hp) / float (knyaz.MAX_HP)) * 100;
    if (knyazHpPercent >= 90) return 1;
    else if (knyazHpPercent >= 80) return 5;
    else if (knyazHpPercent >= 70) return 10;
    else if (knyazHpPercent >= 60) return 20;
    else if (knyazHpPercent >= 50) return 40;
    else if (knyazHpPercent >= 40) return 50;
    else if (knyazHpPercent >= 30) return 60;
    else if (knyazHpPercent >= 20) return 70;
    return 80;
}

void removeBottleByCoords(sf::Vector2f coords) {
    for (auto &entity : mapObjs) {
        auto toRemove = remove_if(mapObjs.begin(), mapObjs.end(), [coords](GameEntity &entity) {return entity.body.getPosition() == coords && entity.type == ObjsTypes::BOTTLE;});
        mapObjs.erase(toRemove, mapObjs.end());
    }
}

void spawnBottle(sf::Vector2f coords) {
    constexpr float BOTTLE_SIDE_SIZE = 15.f;
    sf::RectangleShape bottle;
    bottle.setSize({BOTTLE_SIDE_SIZE, BOTTLE_SIDE_SIZE});
    bottle.setPosition({coords.x, coords.y - BOTTLE_SIDE_SIZE});
    bottle.setTexture(&BottleTexture);

    GameEntity bottleEntity;
    bottleEntity.body = bottle;
    bottleEntity.type = ObjsTypes::BOTTLE;

    mapObjs.emplace_back(bottleEntity);
}