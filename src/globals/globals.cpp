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

sf::Texture GroundTexture;

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

void initMapObj(sf::Vector2f objSize, sf::Vector2f objPos) {
    GameEntity newEntity;

    sf::RectangleShape objBody({objSize});
    objBody.setPosition(objPos);
    objBody.setTexture(&GroundTexture);
    objBody.setTextureRect(sf::IntRect(0, 0, (int)objSize.x, (int)objSize.y));
    newEntity.body = objBody;

    mapObjs.push_back(newEntity);
}

const vector<pair<sf::Vector2f, sf::Vector2f>> mapObjParams {
        make_pair<sf::Vector2f, sf::Vector2f>({20.f, 2000.f}, {-20.f, -1000.f}), //leftWorldEdge
        make_pair<sf::Vector2f, sf::Vector2f>({20.f, 2000.f}, {4320.f, -1000.f}), //rightWorldEdge
        make_pair<sf::Vector2f, sf::Vector2f>({4320.f, 28.f}, {0.f, 771.f}),    //floor

        make_pair<sf::Vector2f, sf::Vector2f>({237.f, 582.f}, {1017.f, 217.f}), //1-end
        make_pair<sf::Vector2f, sf::Vector2f>({237.f, 35.f}, {666.f, 684.f}), //1-1
        make_pair<sf::Vector2f, sf::Vector2f>({237.f, 35.f}, {403.f, 541.f}), //1-2
        make_pair<sf::Vector2f, sf::Vector2f>({237.f, 35.f}, {149.f, 446.f}), //1-3
        make_pair<sf::Vector2f, sf::Vector2f>({237.f, 35.f}, {0.f, 321.f}), //1-4
        make_pair<sf::Vector2f, sf::Vector2f>({237.f, 35.f}, {347.f, 216.f}), //1-5
        make_pair<sf::Vector2f, sf::Vector2f>({367.f, 35.f}, {650.f, 147.f}), //1-6

        make_pair<sf::Vector2f, sf::Vector2f>({20.f, 642.f}, {2860.f, 129.f}), //2-end
        make_pair<sf::Vector2f, sf::Vector2f>({145.f, 35.f}, {2420.f, 676.f}), //2-1
        make_pair<sf::Vector2f, sf::Vector2f>({145.f, 35.f}, {2420.f, 511.f}), //2-2
        make_pair<sf::Vector2f, sf::Vector2f>({145.f, 35.f}, {2420.f, 346.f}), //2-3
        make_pair<sf::Vector2f, sf::Vector2f>({145.f, 35.f}, {2420.f, 181.f}), //2-4
        make_pair<sf::Vector2f, sf::Vector2f>({145.f, 35.f}, {2715.f, 624.f}), //2-5
        make_pair<sf::Vector2f, sf::Vector2f>({145.f, 35.f}, {2715.f, 459.f}), //2-6
        make_pair<sf::Vector2f, sf::Vector2f>({145.f, 35.f}, {2715.f, 294.f}), //2-7
        make_pair<sf::Vector2f, sf::Vector2f>({145.f, 35.f}, {2715.f, 129.f}), //2-8
        make_pair<sf::Vector2f, sf::Vector2f>({20.f, 545.f}, {2400.f, 0.f}), //2-9
};

void initGameMap() {
    for (auto obj : mapObjParams) {
        initMapObj({obj.first.x, obj.first.y}, {obj.second.x, obj.second.y});
    }
}

std::map<std::string, std::string> config;
std::map<std::string, sf::Keyboard::Scancode> keymap;
sf::Clock globalTimer;