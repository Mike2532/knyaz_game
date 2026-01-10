#include "../../types.h"

using namespace std;

#include "./gameEntity/gameEntity.h"
#include "../resources/objs/objs.h"

using MapObj = pair<pair<sf::Vector2f, sf::Vector2f>, ObjsTypes>;
using TextureMap = map<ObjsTypes, sf::Texture*>;

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

const vector<MapObj>  mapObjParams {
        makeEntity({20.f, 2000.f}, {-20.f, -1000.f}, ObjsTypes::ENTITY),      // leftWorldEdge
        makeEntity({20.f, 900.f}, {4320.f, 0}, ObjsTypes::WALL),     //boss door
        makeEntity({20.f, 2000.f}, {4320.f + 1440.f, -1000}, ObjsTypes::WALL),     // rightWorldEdge

        makeEntity({20.f, 180}, {4320.f, -180}, ObjsTypes::ENTITY), //upper boss door

        makeEntity({1000.f, 28.f}, {0.f, 771.f + 100.f}, ObjsTypes::ENTITY),           // floor
        makeEntity({1000.f, 28.f}, {1000.f, 771.f + 100.f}, ObjsTypes::ENTITY),           // floor
        makeEntity({1000.f, 28.f}, {2000.f, 771.f + 100.f}, ObjsTypes::ENTITY),           // floor
        makeEntity({1000.f, 28.f}, {3000.f, 771.f + 100.f}, ObjsTypes::ENTITY),           // floor
        makeEntity({1000.f, 28.f}, {4000.f, 771.f + 100.f}, ObjsTypes::ENTITY),           // floor
        makeEntity({1000.f, 28.f}, {5000.f, 771.f + 100.f}, ObjsTypes::ENTITY),           // floor
        makeEntity({4320.f + 2000.f, 28.f}, {0.f, -180.f}, ObjsTypes::ENTITY),           // rof

//        makeEntity({237.f, 582.f}, {1017.f, 217.f + 100.f}, ObjsTypes::WALL),       // 1-end
//        makeEntity({237.f, 35.f}, {403.f, 541.f + 100.f}, ObjsTypes::ENTITY), // 1-2
//        makeEntity({237.f, 35.f}, {149.f, 446.f + 100.f}, ObjsTypes::ENTITY), // 1-3
//        makeEntity({237.f, 35.f}, {0.f, 321.f + 100.f}, ObjsTypes::ENTITY), // 1-4
//        makeEntity({237.f, 35.f}, {347.f, 216.f + 100.f}, ObjsTypes::ENTITY), // 1-5
//        makeEntity({367.f, 35.f}, {650.f, 147.f + 100.f}, ObjsTypes::ENTITY), // 1-6
//
//        makeEntity({20.f, 642.f}, {2860.f, 129.f + 100.f}, ObjsTypes::ENTITY), // 2-end
//        makeEntity({145.f, 35.f}, {2420.f, 676.f + 100.f}, ObjsTypes::ENTITY), // 2-1
//        makeEntity({145.f, 35.f}, {2420.f, 511.f + 100.f}, ObjsTypes::ENTITY), // 2-2
//        makeEntity({145.f, 35.f}, {2420.f, 346.f + 100.f}, ObjsTypes::ENTITY), // 2-3
//        makeEntity({145.f, 35.f}, {2420.f, 181.f + 100.f}, ObjsTypes::ENTITY), // 2-4
//        makeEntity({145.f, 35.f}, {2715.f, 624.f + 100.f}, ObjsTypes::ENTITY), // 2-5
//        makeEntity({145.f, 35.f}, {2715.f, 459.f + 100.f}, ObjsTypes::ENTITY), // 2-6
//        makeEntity({145.f, 35.f}, {2715.f, 294.f + 100.f}, ObjsTypes::ENTITY), // 2-7
//        makeEntity({145.f, 35.f}, {2715.f, 129.f + 100.f}, ObjsTypes::ENTITY), // 2-8
//        makeEntity({20.f, 945.f}, {2400.f, -400.f + 100.f}, ObjsTypes::ENTITY), // 2-9
//
//        makeEntity({80.f, 680.f}, {1434.f, -180.f + 100.f}, ObjsTypes::WALL), // M1
//        makeEntity({60.f, 535.f}, {1714.f, 236.f + 100.f}, ObjsTypes::WALL), // M2
//        makeEntity({80.f, 35.f}, {1634.f, 236.f + 100.f}, ObjsTypes::WALL), //M3
//
//        makeEntity({30.f, 30.f}, {1647.f, 206.f + 100.f}, ObjsTypes::SPIKES_UP), //SPIKES_UP
//        makeEntity({30.f, 30.f}, {1647.f + 30 * 1, 206.f + 100.f}, ObjsTypes::SPIKES_UP),  //SPIKES_UP
//        makeEntity({30.f, 30.f}, {1647.f + 30 * 2, 206.f + 100.f}, ObjsTypes::SPIKES_UP),  //SPIKES_UP
//        makeEntity({30.f, 30.f}, {1647.f + 30 * 3, 206.f + 100.f}, ObjsTypes::SPIKES_UP),  //SPIKES_UP
//
//        makeEntity({460.f, 50.f}, {1254.f, 721.f + 100.f}, ObjsTypes::OBTACLE),        //lava
//
//        makeEntity({30.f, 30.f}, {2420.f, 151.f + 100.f}, ObjsTypes::SPIKES), //spike1
//        makeEntity({30.f, 30.f}, {2420.f, 151.f - 30 * 1 + 100.f}, ObjsTypes::SPIKES), //spike2
//        makeEntity({30.f, 30.f}, {2420.f, 151.f - 30 * 2 + 100.f}, ObjsTypes::SPIKES), //spike3
//        makeEntity({30.f, 30.f}, {2420.f, 151.f - 30 * 3 + 100.f}, ObjsTypes::SPIKES), //spike4
//        makeEntity({30.f, 30.f}, {2420.f, 151.f - 30 * 4 + 100.f}, ObjsTypes::SPIKES), //spike5
//        makeEntity({30.f, 30.f}, {2420.f, 151.f - 30 * 5 + 100.f}, ObjsTypes::SPIKES), //spike6
//
//        makeEntity({30.f, 30.f}, {0.f, 151.f * 2 - 30 * 1 + 100.f}, ObjsTypes::SPIKES), //start-low spike
//        makeEntity({30.f, 30.f}, {0.f, 151.f * 2 - 30 * 2 + 100.f}, ObjsTypes::SPIKES), //start-low spike
//        makeEntity({30.f, 30.f}, {0.f, 151.f * 2 - 30 * 3 + 100.f}, ObjsTypes::SPIKES), //start-low spike
//        makeEntity({30.f, 30.f}, {0.f, 151.f * 2 - 30 * 4 + 100.f}, ObjsTypes::SPIKES), //start-low spike
//        makeEntity({30.f, 30.f}, {0.f, 151.f * 2 - 30 * 5 + 100.f}, ObjsTypes::SPIKES), //start-low spike
//
//        makeEntity({30.f, 30.f}, {0.f, 151.f - 30 * 1 + 100.f}, ObjsTypes::SPIKES), //start-hight spike
//        makeEntity({30.f, 30.f}, {0.f, 151.f - 30 * 2 + 100.f}, ObjsTypes::SPIKES), //start-hight spike
//        makeEntity({30.f, 30.f}, {0.f, 151.f - 30 * 3 + 100.f}, ObjsTypes::SPIKES), //start-hight spike
//        makeEntity({30.f, 30.f}, {0.f, 151.f - 30 * 4 + 100.f}, ObjsTypes::SPIKES), //start-hight spike
//        makeEntity({30.f, 30.f}, {0.f, 151.f - 30 * 5 + 100.f}, ObjsTypes::SPIKES), //start-hight spike
//
//        makeEntity({120.f, 35.f}, {2880.f, 736.f + 100.f}, ObjsTypes::OBTACLE), //4zone lava One
//
//        makeEntity({573.f, 500.f}, {2970.f, -500.f + 100.f}, ObjsTypes::ENTITY),    //4zone BIGSQUARE UPPROPTECTION
//        makeEntity({573.f, 560.f}, {2970.f, 0.f + 100.f}, ObjsTypes::WALL),         //4zone BIGSQUARE
//        makeEntity({543.f, 35.f}, {3000.f, 736.f + 100.f}, ObjsTypes::ENTITY),      //4zone goblin-platform
//        makeEntity({91.f, 711.f + 100.f}, {3543.f, 0.f + 100.f}, ObjsTypes::ENTITY), //4zone portalWall 1
//        makeEntity({100.f, 35.f}, {3634.f, 736.f + 100.f}, ObjsTypes::ENTITY),      //4zone portalFloor
//        makeEntity({100.f + 120.f, 35.f + 100.f}, {3634.f - 100.f, 0.f}, ObjsTypes::ENTITY), //4zone portalRoof
//        makeEntity({20.f, 771.f}, {3734.f, 0.f + 100.f}, ObjsTypes::ENTITY),        //4zone anti-gravity right wall
//        makeEntity({20.f, 500.f}, {3754.f, -500.f + 100.f}, ObjsTypes::ENTITY),     //4zone battle arena left wall UPPER PROTECTION
//        makeEntity({20.f, 771.f}, {3754.f, 0.f + 100.f}, ObjsTypes::WALL),          //4zone battle arena left wall
//
//        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 0 + 100.f}, ObjsTypes::SPIKES), //4zone battle arena spikes
//        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 1 + 100.f}, ObjsTypes::SPIKES), //4zone battle arena spikes
//        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 2 + 100.f}, ObjsTypes::SPIKES), //4zone battle arena spikes
//        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 3 + 100.f}, ObjsTypes::SPIKES), //4zone battle arena spikes
//        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 4 + 100.f}, ObjsTypes::SPIKES), //4zone battle arena spikes
//        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 5 + 100.f}, ObjsTypes::SPIKES), //4zone battle arena spikes
//        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 6 + 100.f}, ObjsTypes::SPIKES), //4zone battle arena spikes
//        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 7 + 100.f}, ObjsTypes::SPIKES), //4zone battle arena spikes
//        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 8 + 100.f}, ObjsTypes::SPIKES), //4zone battle arena spikes
//        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 9 + 100.f}, ObjsTypes::SPIKES), //4zone battle arena spikes
//        makeEntity({30.f, 30.f}, {3774.f, 0.f + 30.f * 10 + 100.f}, ObjsTypes::SPIKES), //4zone battle arena spikes
//
//        makeEntity({80.f + 65.f, 135.f + 100.f}, {4240.f - 65.f, 0.f}, ObjsTypes::ENTITY), //4zone portalWall2
//        makeEntity({335.f, 35.f}, {3905.f, 100.f + 100.f}, ObjsTypes::ENTITY), //4zone foor near portal
//        makeEntity({131.f, 70.f}, {3774.f, 330.f + 100.f}, ObjsTypes::ENTITY), //4zone platform under spikes
//        makeEntity({302.f, 35.f}, {3903.f, 365.f + 100.f}, ObjsTypes::ENTITY), //4zone platform for spikes
//
//        makeEntity({30.f, 30.f}, {3905.f + 30 * 0, 335.f + 100.f}, ObjsTypes::SPIKES_UP), //4zone long spikes
//        makeEntity({30.f, 30.f}, {3905.f + 30 * 1, 335.f + 100.f}, ObjsTypes::SPIKES_UP), //4zone long spikes
//        makeEntity({30.f, 30.f}, {3905.f + 30 * 2, 335.f + 100.f}, ObjsTypes::SPIKES_UP), //4zone long spikes
//        makeEntity({30.f, 30.f}, {3905.f + 30 * 3, 335.f + 100.f}, ObjsTypes::SPIKES_UP), //4zone long spikes
//        makeEntity({30.f, 30.f}, {3905.f + 30 * 4, 335.f + 100.f}, ObjsTypes::SPIKES_UP), //4zone long spikes
//        makeEntity({30.f, 30.f}, {3905.f + 30 * 5, 335.f + 100.f}, ObjsTypes::SPIKES_UP), //4zone long spikes
//        makeEntity({30.f, 30.f}, {3905.f + 30 * 6, 335.f + 100.f}, ObjsTypes::SPIKES_UP), //4zone long spikes
//        makeEntity({30.f, 30.f}, {3905.f + 30 * 7, 335.f + 100.f}, ObjsTypes::SPIKES_UP), //4zone long spikes
//        makeEntity({30.f, 30.f}, {3905.f + 30 * 8, 335.f + 100.f}, ObjsTypes::SPIKES_UP), //4zone long spikes
//        makeEntity({30.f, 30.f}, {3905.f + 30 * 9, 335.f + 100.f}, ObjsTypes::SPIKES_UP), //4zone long spikes
//
//        makeEntity({335.f, 35.f}, {3985.f, 495.f + 100.f}, ObjsTypes::ENTITY), //4zone dls platform 1
//        makeEntity({338.f, 35.f}, {3774.f, 616.f + 100.f}, ObjsTypes::ENTITY), //4zone dls platform 2
//        makeEntity({150.f, 35.f}, {4170.f, 616.f + 100.f}, ObjsTypes::ENTITY), //4zone dls platform 3
//
//        makeEntity({30.f, 30.f}, {3774.f, 400.f + 100.f + 30.f * 0}, ObjsTypes::SPIKES), //4zone spikes upper plat2
//        makeEntity({30.f, 30.f}, {3774.f, 400.f + 100.f + 30.f * 1}, ObjsTypes::SPIKES), //4zone spikes upper plat2
//        makeEntity({30.f, 30.f}, {3774.f, 400.f + 100.f + 30.f * 2}, ObjsTypes::SPIKES), //4zone spikes upper plat2
//        makeEntity({30.f, 30.f}, {3774.f, 400.f + 100.f + 30.f * 3}, ObjsTypes::SPIKES), //4zone spikes upper plat2
//
//        makeEntity({30.f, 30.f}, {4171.f + 30.f * 0, 586.f + 100.f}, ObjsTypes::SPIKES_UP), //4zone spikes upper plat3
//        makeEntity({30.f, 30.f}, {4171.f + 30.f * 1, 586.f + 100.f}, ObjsTypes::SPIKES_UP), //4zone spikes upper plat3
//        makeEntity({30.f, 30.f}, {4171.f + 30.f * 2, 586.f + 100.f}, ObjsTypes::SPIKES_UP), //4zone spikes upper plat3
//        makeEntity({30.f, 30.f}, {4171.f + 30.f * 3, 586.f + 100.f}, ObjsTypes::SPIKES_UP), //4zone spikes upper plat3
//        makeEntity({30.f, 30.f}, {4171.f + 30.f * 4, 586.f + 100.f}, ObjsTypes::SPIKES_UP), //4zone spikes upper plat3

        makeEntity({237.f, 35.f}, {4543.f, 530.f + 100.f}, ObjsTypes::ENTITY),     //boos platform 1
        makeEntity({30.f, 30.f}, {4541.f, 497.f + 105.f}, ObjsTypes::SPIKES_UP),     //boos spikes upper p1
        makeEntity({30.f, 30.f}, {4748.f, 497.f + 105.f}, ObjsTypes::SPIKES_UP),     //boos spikes upper p1

        makeEntity({237.f, 35.f}, {4979.f, 530.f + 100.f}, ObjsTypes::ENTITY),     //boos platform 2
        makeEntity({30.f, 30.f}, {5055.f, 497.f + 105.f}, ObjsTypes::SPIKES_UP),     //boos spikes upper p2
        makeEntity({30.f, 30.f}, {5055.f + 30.f, 497.f + 105.f}, ObjsTypes::SPIKES_UP),     //boos spikes upper p2
        makeEntity({30.f, 30.f}, {5055.f + 60.f, 497.f + 105.f}, ObjsTypes::SPIKES_UP),     //boos spikes upper p2

        makeEntity({237.f, 35.f}, {5455.f, 530.f + 100.f}, ObjsTypes::ENTITY),     //boos platform 3
        makeEntity({30.f, 30.f}, {5455.f, 497.f + 105.f}, ObjsTypes::SPIKES_UP),     //boos spikes upper p3
        makeEntity({30.f, 30.f}, {5662.f, 497.f + 105.f}, ObjsTypes::SPIKES_UP),     //boos spikes upper p3

        makeEntity({237.f, 35.f}, {4683.f, 283.f + 100.f}, ObjsTypes::ENTITY),     //boos platform 4
        makeEntity({30.f, 30.f}, {4683.f, 253.f + 105.f}, ObjsTypes::SPIKES_UP),     //boos spikes upper p4
        makeEntity({30.f, 30.f}, {4683.f + 30.f, 253.f + 105.f}, ObjsTypes::SPIKES_UP),     //boos spikes upper p4
        makeEntity({30.f, 30.f}, {4860.f, 253.f + 105.f}, ObjsTypes::SPIKES_UP),     //boos spikes upper p4
        makeEntity({30.f, 30.f}, {4860.f + 30.f, 253.f + 105.f}, ObjsTypes::SPIKES_UP),     //boos spikes upper p4

        makeEntity({237.f, 35.f}, {5231.f, 283.f + 100.f}, ObjsTypes::ENTITY),     //boos platform 5
        makeEntity({30.f, 30.f}, {5231.f, 253.f + 100.f}, ObjsTypes::SPIKES_UP),     //boos spikes upper p5
        makeEntity({30.f, 30.f}, {5231.f + 30.f, 253.f + 100.f}, ObjsTypes::SPIKES_UP),     //boos spikes upper p5
        makeEntity({30.f, 30.f}, {5408.f, 253.f + 100.f}, ObjsTypes::SPIKES_UP),     //boos spikes upper p5
        makeEntity({30.f, 30.f}, {5408.f + 30.f, 253.f + 100.f}, ObjsTypes::SPIKES_UP),     //boos spikes upper p5

        makeEntity({237.f, 35.f}, {4979.f, 112.f + 100.f}, ObjsTypes::ENTITY),     //boos platform 6
        makeEntity({30.f, 30.f}, {5055.f, 84.f + 100.f}, ObjsTypes::SPIKES_UP),     //boos spikes upper p6
        makeEntity({30.f, 30.f}, {5055.f + 30.f, 84.f + 100.f}, ObjsTypes::SPIKES_UP),     //boos spikes upper p6
        makeEntity({30.f, 30.f}, {5055.f + 60.f, 84.f + 100.f}, ObjsTypes::SPIKES_UP),     //boos spikes upper p6
};

void certainInit(MapObj& obj, sf::Texture& texture) {
    initMapObj(
        {obj.first.first.x, obj.first.first.y},
        {obj.first.second.x, obj.first.second.y},
        texture,
        mapObjs,
        obj.second
    );
}

TextureMap getTextureMap() {
    sf::Texture emptyTexture;

    map<ObjsTypes, sf::Texture*> textureMap;
    textureMap[ObjsTypes::OBTACLE]      = &LavaTexture;
    textureMap[ObjsTypes::ENTITY]       = &GroundTexture;
    textureMap[ObjsTypes::WALL]         = &GroundTexture;
    textureMap[ObjsTypes::SPIKES]       = &SpikesTexture;
    textureMap[ObjsTypes::SPIKES_UP]    = &SpikesUpTexture;
    textureMap[ObjsTypes::ENEMY]        = &emptyTexture;

    return textureMap;
}

void initGameMap() {
    mapObjs.clear();
    for (auto obj : mapObjParams) {
        TextureMap textureMap = getTextureMap();
        sf::Texture* objTexture = textureMap[obj.second];
        certainInit(obj, *objTexture);
    }
}