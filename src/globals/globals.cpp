#include "globals.h"
#include "../types.h"
#include "string"

using namespace std;

sf::Texture MainMenuTexture;
sf::Texture HelpMenuTexture;
sf::Texture LoadScreenOneTexture;
sf::Texture LoadScreenTwoTexture;
sf::Texture GameProcessTexture;
sf::Texture GameEndTexture;

sf::Texture KnyazIdleTexture;
sf::Texture KnyazRunTexture;
sf::Texture KnyazJumpTexture;
sf::Texture KnyazFallingTexture;
sf::Texture KnyazEasyAttackTexture;
sf::Texture KnyazHeavyAttackTexture;
sf::Texture KnyazDeathTexture;
sf::Texture KnyazWallHangTexture;

sf::Texture HpIndicatorTexture;

sf::Texture EnemyWalkTexture;
sf::Texture EnemyAttackTexture;
sf::Texture EnemyIDLETexture;

sf::Texture GroundTexture;
sf::Texture LavaTexture;
sf::Texture SpikesTexture;
sf::Texture SpikesUpTexture;

sf::Texture BottleTexture;

sf::Music GameMusic;
sf::Font myFont;
sf::Sprite BGSprite;
sf::Sprite HpIndicatorSprite;

std::map<std::string, AnimationData> animationContainer;

Knyaz knyaz;
MainMenu mainMenu;
SettingsMenu settingsMenu;
sf::RenderWindow window;

//TODO в прод разкомментировать
//GameState curState = GameState::MAIN_MENU;
//TODO в прод закомментировать
GameState curState = GameState::GAME_PROCESS;

vector<GameEntity> mapObjs;
vector<Enemy> mapEnemys;

void initMapObj(sf::Vector2f objSize, sf::Vector2f objPos, sf::Texture &texture, vector<GameEntity> &container, ObjsTypes type) {
    GameEntity newEntity;

    sf::RectangleShape objBody({objSize});
    objBody.setPosition(objPos);
    objBody.setTexture(&texture);
    if (type != ObjsTypes::SPIKES && type != ObjsTypes::SPIKES_UP) objBody.setTextureRect(sf::IntRect(0, 0, (int)objSize.x, (int)objSize.y));
    if (type == ObjsTypes::ENEMY) objBody.setFillColor(sf::Color::Red); //TODO удалить
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

struct EnemyParam {
    const sf::Vector2f enemyPos;
    const float LEFT_ACTIVE_EDGE;
    const float LEFT_PATROLING_EDGE;
    const float RIGHT_PATROLING_EDGE;
    const float RIGHT_ACTIVE_EDGE;
};

auto addEnemy(const EnemyParam &enemyParam) {
    Enemy myEnemy;
    myEnemy.body.setSize({50.f, 60.f});
    myEnemy.body.setPosition(enemyParam.enemyPos);
    myEnemy.LEFT_ACTIVE_EDGE = enemyParam.LEFT_ACTIVE_EDGE;
    myEnemy.LEFT_PATROLING_EDGE = enemyParam.LEFT_PATROLING_EDGE;
    myEnemy.RIGHT_PATROLING_EDGE = enemyParam.RIGHT_PATROLING_EDGE;
    myEnemy.RIGHT_ACTIVE_EDGE = enemyParam.RIGHT_ACTIVE_EDGE;
    myEnemy.animationData = animationContainer["enemyWalk"];
    mapEnemys.push_back(myEnemy);
}

const vector<EnemyParam> enemyParams {
        { //MW
                {1932.f, 691.f + 20.f - 2.f},
                1774.f,
                1899.f,
                2290.f,
                2420.f
        },
        { //Start 1-st
                {466.f, 461.f + 20.f - 2.f},
                407.f,
                407.f,
                653.f,
                653.f
        },
        { //Start 2-nd
                {702.f, 67.f + 20.f - 2.f},
                655.f,
                680.f,
                982.f,
                1012.f
        },
        {  //Tower 1-st
                {2435.f, 431.f + 20.f - 2.f},
                2425.f,
                2425.f,
                2560.f,
                2560.f
        },
        { //Tower 2-nd
                {2770.f, 214.f + 20.f - 2.f},
                2720.f,
                2720.f,
                2855.f,
                2855.f
        }
};

void initEnemys() {
    mapEnemys.clear();
    for (auto &enemyParam : enemyParams) {
        addEnemy(enemyParam);
    }
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

std::map<std::string, std::string> config;
std::map<std::string, sf::Keyboard::Scancode> keymap;
sf::Clock globalTimer;

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

void enemysTakenDamage() {
    constexpr int ATTACK_DELAY = 200;
    if (knyaz.attackTimer.getElapsedTime().asMilliseconds() >= ATTACK_DELAY && knyaz.isAttackFinished) {
        for (auto &enemy : mapEnemys) {
            if (enemy.takenDamage != 0) {
                enemy.hp -= enemy.takenDamage;
                enemy.takenDamage = 0;
                enemy.objSprite.setColor(sf::Color::White);
                if (enemy.hp <= 0) {
                    int chanse = getBottleSpawnChanse();
                    int r2 = rand() % 100;
                    if (r2 <= chanse) {
                        sf::Vector2f pos = enemy.body.getPosition();
                        sf::Vector2f size = enemy.body.getSize();

                        float bottleXPos = pos.x + (size.x/2);
                        float bottleYPos = pos.y + (size.y);

                        spawnBottle({bottleXPos, bottleYPos});
                    }
                }
            }
        }
        knyaz.isAttackFinished = false;
    }
}

void removeBottleByCoords(sf::Vector2f coords) {
    for (auto &entity : mapObjs) {
        auto toRemove = remove_if(mapObjs.begin(), mapObjs.end(), [coords](GameEntity &entity) {return entity.body.getPosition() == coords && entity.type == ObjsTypes::BOTTLE;});
        mapObjs.erase(toRemove, mapObjs.end());
    }
}