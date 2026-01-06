#include "../../types.h"

using namespace std;

#include "./gameEntity/gameEntity.h"
#include "../resources/objs/objs.h"

vector<GameEntity> mapObjs;

void initMapObj(sf::Vector2f objSize, sf::Vector2f objPos, sf::Texture &texture, vector<GameEntity> &container, ObjsTypes type) {
    GameEntity newEntity;

    sf::RectangleShape objBody({objSize});
    objBody.setPosition(objPos);
    objBody.setTexture(&texture);
    if (type != ObjsTypes::SPIKES && type != ObjsTypes::SPIKES_UP) objBody.setTextureRect(sf::IntRect(0, 0, (int)objSize.x, (int)objSize.y));
    newEntity.body = objBody;

    newEntity.type = type;

    container.push_back(newEntity);
}

auto makeEntity(const sf::Vector2f &entitySize, const sf::Vector2f &entityPos, ObjsTypes entityType) {
    return std::make_pair(
            std::make_pair(entitySize, entityPos),
            entityType
    );
}

const vector<pair<pair<sf::Vector2f, sf::Vector2f>, ObjsTypes>>  mapObjParams {
        makeEntity({20.f, 2000.f}, {-20.f, -1000.f}, ObjsTypes::ENTITY),      // leftWorldEdge
        makeEntity({20.f, 2000.f}, {4320.f, -1000.f}, ObjsTypes::ENTITY),     // rightWorldEdge
        makeEntity({4320.f, 28.f}, {0.f, 771.f}, ObjsTypes::ENTITY),           // floor
        makeEntity({4320.f, 28.f}, {0.f, -180.f}, ObjsTypes::ENTITY),           // rof

        makeEntity({237.f, 582.f}, {1017.f, 217.f}, ObjsTypes::WALL),       // 1-end
        makeEntity({237.f, 35.f}, {666.f, 684.f}, ObjsTypes::ENTITY), // 1-1
        makeEntity({237.f, 35.f}, {403.f, 541.f}, ObjsTypes::ENTITY), // 1-2
        makeEntity({237.f, 35.f}, {149.f, 446.f}, ObjsTypes::ENTITY), // 1-3
        makeEntity({237.f, 35.f}, {0.f, 321.f}, ObjsTypes::ENTITY), // 1-4
        makeEntity({237.f, 35.f}, {347.f, 216.f}, ObjsTypes::ENTITY), // 1-5
        makeEntity({367.f, 35.f}, {650.f, 147.f}, ObjsTypes::ENTITY), // 1-6

        makeEntity({20.f, 642.f}, {2860.f, 129.f}, ObjsTypes::WALL), // 2-end
        makeEntity({145.f, 35.f}, {2420.f, 676.f}, ObjsTypes::ENTITY), // 2-1
        makeEntity({145.f, 35.f}, {2420.f, 511.f}, ObjsTypes::ENTITY), // 2-2
        makeEntity({145.f, 35.f}, {2420.f, 346.f}, ObjsTypes::ENTITY), // 2-3
        makeEntity({145.f, 35.f}, {2420.f, 181.f}, ObjsTypes::ENTITY), // 2-4
        makeEntity({145.f, 35.f}, {2715.f, 624.f}, ObjsTypes::ENTITY), // 2-5
        makeEntity({145.f, 35.f}, {2715.f, 459.f}, ObjsTypes::ENTITY), // 2-6
        makeEntity({145.f, 35.f}, {2715.f, 294.f}, ObjsTypes::ENTITY), // 2-7
        makeEntity({145.f, 35.f}, {2715.f, 129.f}, ObjsTypes::ENTITY), // 2-8
        makeEntity({20.f, 945.f}, {2400.f, -400.f}, ObjsTypes::WALL), // 2-9

        makeEntity({80.f, 680.f}, {1434.f, -180.f}, ObjsTypes::WALL), // M1
        makeEntity({60.f, 535.f}, {1714.f, 236.f}, ObjsTypes::WALL), // M2
        makeEntity({80.f, 35.f}, {1634.f, 236.f}, ObjsTypes::WALL), //M3

        makeEntity({30.f, 30.f}, {1647.f, 206.f}, ObjsTypes::SPIKES_UP), //SPIKES_UP
        makeEntity({30.f, 30.f}, {1647.f + 30 * 1, 206.f}, ObjsTypes::SPIKES_UP),  //SPIKES_UP
        makeEntity({30.f, 30.f}, {1647.f + 30 * 2, 206.f}, ObjsTypes::SPIKES_UP),  //SPIKES_UP
        makeEntity({30.f, 30.f}, {1647.f + 30 * 3, 206.f}, ObjsTypes::SPIKES_UP),  //SPIKES_UP

        makeEntity({460.f, 50.f}, {1254.f, 721.f}, ObjsTypes::OBTACLE),        //lava

        makeEntity({30.f, 30.f}, {2420.f, 151.f}, ObjsTypes::SPIKES), //ship1
        makeEntity({30.f, 30.f}, {2420.f, 151.f - 30 * 1}, ObjsTypes::SPIKES), //ship2
        makeEntity({30.f, 30.f}, {2420.f, 151.f - 30 * 2}, ObjsTypes::SPIKES), //ship3
        makeEntity({30.f, 30.f}, {2420.f, 151.f - 30 * 3}, ObjsTypes::SPIKES), //ship4
        makeEntity({30.f, 30.f}, {2420.f, 151.f - 30 * 4}, ObjsTypes::SPIKES), //ship5
        makeEntity({30.f, 30.f}, {2420.f, 151.f - 30 * 5}, ObjsTypes::SPIKES), //ship6

        makeEntity({30.f, 30.f}, {0.f, 151.f * 2 - 30 * 1}, ObjsTypes::SPIKES), //start-low ship
        makeEntity({30.f, 30.f}, {0.f, 151.f * 2 - 30 * 2}, ObjsTypes::SPIKES), //start-low ship
        makeEntity({30.f, 30.f}, {0.f, 151.f * 2 - 30 * 3}, ObjsTypes::SPIKES), //start-low ship
        makeEntity({30.f, 30.f}, {0.f, 151.f * 2 - 30 * 4}, ObjsTypes::SPIKES), //start-low ship
        makeEntity({30.f, 30.f}, {0.f, 151.f * 2 - 30 * 5}, ObjsTypes::SPIKES), //start-low ship

        makeEntity({30.f, 30.f}, {0.f, 151.f - 30 * 1}, ObjsTypes::SPIKES), //start-hight ship
        makeEntity({30.f, 30.f}, {0.f, 151.f - 30 * 2}, ObjsTypes::SPIKES), //start-hight ship
        makeEntity({30.f, 30.f}, {0.f, 151.f - 30 * 3}, ObjsTypes::SPIKES), //start-hight ship
        makeEntity({30.f, 30.f}, {0.f, 151.f - 30 * 4}, ObjsTypes::SPIKES), //start-hight ship
        makeEntity({30.f, 30.f}, {0.f, 151.f - 30 * 5}, ObjsTypes::SPIKES), //start-hight ship

        makeEntity({120.f, 35.f}, {2880.f, 736.f}, ObjsTypes::OBTACLE), //4zone lava One

        makeEntity({573.f, 500.f}, {2970.f, -500.f}, ObjsTypes::ENTITY), //4zone BIGSQUARE UPPROPTECTION
        makeEntity({573.f, 560.f}, {2970.f, 0.f}, ObjsTypes::WALL), //4zone BIGSQUARE
        makeEntity({543.f, 35.f}, {3000.f, 736.f}, ObjsTypes::ENTITY), //4zone goblin-platform
        makeEntity({91.f, 711.f + 100.f}, {3543.f, 0.f}, ObjsTypes::ENTITY), //4zone portalWall 1
        makeEntity({100.f, 35.f}, {3634.f, 736.f}, ObjsTypes::ENTITY), //4zone portalFloor
        makeEntity({100.f, 35.f}, {3634.f, 0.f}, ObjsTypes::ENTITY), //4zone portalRoof
        makeEntity({20.f, 771.f}, {3734.f, 0.f}, ObjsTypes::ENTITY), //4zone anti-gravity right wall
        makeEntity({20.f, 500.f}, {3754.f, -500.f}, ObjsTypes::ENTITY), //4zone battle arena left wall UPPER PROTECTION
        makeEntity({20.f, 771.f}, {3754.f, 0.f}, ObjsTypes::WALL), //4zone battle arena left wall

        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 0}, ObjsTypes::SPIKES), //4zone battle arena spikes
        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 1}, ObjsTypes::SPIKES), //4zone battle arena spikes
        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 2}, ObjsTypes::SPIKES), //4zone battle arena spikes
        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 3}, ObjsTypes::SPIKES), //4zone battle arena spikes
        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 4}, ObjsTypes::SPIKES), //4zone battle arena spikes
        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 5}, ObjsTypes::SPIKES), //4zone battle arena spikes
        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 6}, ObjsTypes::SPIKES), //4zone battle arena spikes
        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 7}, ObjsTypes::SPIKES), //4zone battle arena spikes
        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 8}, ObjsTypes::SPIKES), //4zone battle arena spikes
        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 9}, ObjsTypes::SPIKES), //4zone battle arena spikes
        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 10}, ObjsTypes::SPIKES), //4zone battle arena spikes

        makeEntity({80.f, 135.f}, {4240.f, 0.f}, ObjsTypes::ENTITY), //4zone portalWall2
        makeEntity({335.f, 35.f}, {3905.f, 100.f}, ObjsTypes::ENTITY), //4zone foor near portal
        makeEntity({131.f, 70.f}, {3774.f, 330.f}, ObjsTypes::ENTITY), //4zone platform under sheeps
        makeEntity({302.f, 35.f}, {3903.f, 365.f}, ObjsTypes::ENTITY), //4zone platform for sheeps

        makeEntity({30.f, 30.f}, {3905.f + 30 * 0, 335.f}, ObjsTypes::SPIKES_UP), //4zone long sheeps
        makeEntity({30.f, 30.f}, {3905.f + 30 * 1, 335.f}, ObjsTypes::SPIKES_UP), //4zone long sheeps
        makeEntity({30.f, 30.f}, {3905.f + 30 * 2, 335.f}, ObjsTypes::SPIKES_UP), //4zone long sheeps
        makeEntity({30.f, 30.f}, {3905.f + 30 * 3, 335.f}, ObjsTypes::SPIKES_UP), //4zone long sheeps
        makeEntity({30.f, 30.f}, {3905.f + 30 * 4, 335.f}, ObjsTypes::SPIKES_UP), //4zone long sheeps
        makeEntity({30.f, 30.f}, {3905.f + 30 * 5, 335.f}, ObjsTypes::SPIKES_UP), //4zone long sheeps
        makeEntity({30.f, 30.f}, {3905.f + 30 * 6, 335.f}, ObjsTypes::SPIKES_UP), //4zone long sheeps
        makeEntity({30.f, 30.f}, {3905.f + 30 * 7, 335.f}, ObjsTypes::SPIKES_UP), //4zone long sheeps
        makeEntity({30.f, 30.f}, {3905.f + 30 * 8, 335.f}, ObjsTypes::SPIKES_UP), //4zone long sheeps
        makeEntity({30.f, 30.f}, {3905.f + 30 * 9, 335.f}, ObjsTypes::SPIKES_UP), //4zone long sheeps
};

void initGameMap() {
    mapObjs.clear();
    for (auto obj : mapObjParams) {
        sf::Texture emptyTexture;

        switch (obj.second) {
            case ObjsTypes::OBTACLE:
                initMapObj({obj.first.first.x, obj.first.first.y}, {obj.first.second.x, obj.first.second.y}, LavaTexture, mapObjs, obj.second);
                break;
            case ObjsTypes::ENTITY:
                initMapObj({obj.first.first.x, obj.first.first.y}, {obj.first.second.x, obj.first.second.y}, GroundTexture, mapObjs, obj.second);
                break;
            case ObjsTypes::WALL:
                initMapObj({obj.first.first.x, obj.first.first.y}, {obj.first.second.x, obj.first.second.y}, GroundTexture, mapObjs, obj.second);
                break;
            case ObjsTypes::SPIKES:
                initMapObj({obj.first.first.x, obj.first.first.y}, {obj.first.second.x, obj.first.second.y}, SpikesTexture, mapObjs, obj.second);
                break;
            case ObjsTypes::SPIKES_UP:
                initMapObj({obj.first.first.x, obj.first.first.y}, {obj.first.second.x, obj.first.second.y}, SpikesUpTexture, mapObjs, obj.second);
                break;
            case ObjsTypes::ENEMY:
                initMapObj({obj.first.first.x, obj.first.first.y}, {obj.first.second.x, obj.first.second.y}, emptyTexture, mapObjs, obj.second);
                break;
        }
    }
}