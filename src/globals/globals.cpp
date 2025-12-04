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

sf::Texture GroundTexture;
sf::Texture LavaTexture;

sf::Music GameMusic;
sf::Font myFont;
sf::Sprite BGSprite;

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
vector<GameEntity> mapObtacles;

void initMapObj(sf::Vector2f objSize, sf::Vector2f objPos, sf::Texture &texture, vector<GameEntity> &container, ObjsTypes type) {
    GameEntity newEntity;

    sf::RectangleShape objBody({objSize});
    objBody.setPosition(objPos);
    objBody.setTexture(&texture);
    objBody.setTextureRect(sf::IntRect(0, 0, (int)objSize.x, (int)objSize.y));
    newEntity.body = objBody;

    newEntity.type = type;

    container.push_back(newEntity);
}

const vector<pair<sf::Vector2f, sf::Vector2f>> mapObtaclesParams {
        make_pair<sf::Vector2f, sf::Vector2f>({400.f, 50.f}, {1254.f, 721.f}), //lava
};


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

        makeEntity({237.f, 582.f}, {1017.f, 217.f}, ObjsTypes::ENTITY),       // 1-end
        makeEntity({237.f, 35.f}, {666.f, 684.f}, ObjsTypes::ENTITY),          // 1-1
        makeEntity({237.f, 35.f}, {403.f, 541.f}, ObjsTypes::ENTITY),          // 1-2
        makeEntity({237.f, 35.f}, {149.f, 446.f}, ObjsTypes::ENTITY),          // 1-3
        makeEntity({237.f, 35.f}, {0.f, 321.f}, ObjsTypes::ENTITY),            // 1-4
        makeEntity({237.f, 35.f}, {347.f, 216.f}, ObjsTypes::ENTITY),          // 1-5
        makeEntity({367.f, 35.f}, {650.f, 147.f}, ObjsTypes::ENTITY),          // 1-6

        makeEntity({80.f, 850.f}, {1434.f, -400.f}, ObjsTypes::ENTITY),        // M1
        makeEntity({120.f, 120.f + 100}, {1654.f, 651.f - 100}, ObjsTypes::ENTITY), // M2

        makeEntity({20.f, 642.f}, {2860.f, 129.f}, ObjsTypes::ENTITY),         // 2-end
        makeEntity({145.f, 35.f}, {2420.f, 676.f}, ObjsTypes::ENTITY),         // 2-1
        makeEntity({145.f, 35.f}, {2420.f, 511.f}, ObjsTypes::ENTITY),         // 2-2
        makeEntity({145.f, 35.f}, {2420.f, 346.f}, ObjsTypes::ENTITY),         // 2-3
        makeEntity({145.f, 35.f}, {2420.f, 181.f}, ObjsTypes::ENTITY),         // 2-4
        makeEntity({145.f, 35.f}, {2715.f, 624.f}, ObjsTypes::ENTITY),         // 2-5
        makeEntity({145.f, 35.f}, {2715.f, 459.f}, ObjsTypes::ENTITY),         // 2-6
        makeEntity({145.f, 35.f}, {2715.f, 294.f}, ObjsTypes::ENTITY),         // 2-7
        makeEntity({145.f, 35.f}, {2715.f, 129.f}, ObjsTypes::ENTITY),         // 2-8
        makeEntity({20.f, 945.f}, {2400.f, -400.f}, ObjsTypes::ENTITY),        // 2-9

        makeEntity({400.f, 50.f}, {1254.f, 721.f}, ObjsTypes::OBTACLE),        //lava
};

void initGameMap() {
    mapObjs.clear();
    for (auto obj : mapObjParams) {
        switch (obj.second) {
            case ObjsTypes::OBTACLE:
                initMapObj({obj.first.first.x, obj.first.first.y}, {obj.first.second.x, obj.first.second.y}, LavaTexture, mapObjs, obj.second);
                break;
            case ObjsTypes::ENTITY:
                initMapObj({obj.first.first.x, obj.first.first.y}, {obj.first.second.x, obj.first.second.y}, GroundTexture, mapObjs, obj.second);
                break;
        }
    }
}

std::map<std::string, std::string> config;
std::map<std::string, sf::Keyboard::Scancode> keymap;
sf::Clock globalTimer;