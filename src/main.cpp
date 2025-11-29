#include "globals/globals.h"
#include "resources/resources.h"
#include "ui/ui.h"
#include "knyaz/knyaz.h"
#include "types.h"
#include "vector"
#include <iostream>
#include "cmath"

using namespace std;

extern std::map<std::string, std::string> initConfig();
extern std::map<std::string, sf::Keyboard::Scancode> getKeymap();

void pollEvents();
void update(std::vector<sf::Text>& textToPrint);
void redrawFrame(const std::vector<sf::Text>& textToPrint);

vector<GameEntity> mapObjs;

void initMapObj(sf::Vector2f objSize, sf::Vector2f objPos) {
    GameEntity newEntity;

    sf::RectangleShape objBody({objSize});
    objBody.setPosition(objPos);
    objBody.setFillColor(sf::Color::Green);
    newEntity.body = objBody;

    mapObjs.push_back(newEntity);
}

const vector<pair<sf::Vector2f, sf::Vector2f>> mapObjParams {
    make_pair<sf::Vector2f, sf::Vector2f>({20.f, 2000.f}, {-20.f, -1000.f}), //leftWorldEdge
    make_pair<sf::Vector2f, sf::Vector2f>({20.f, 2000.f}, {4320.f, -1000.f}), //rightWorldEdge
    make_pair<sf::Vector2f, sf::Vector2f>({4320.f, 28.f}, {0.f, 771.f}),    //floor

    //todo закомментировано только для теста
    make_pair<sf::Vector2f, sf::Vector2f>({237.f, 582.f}, {1017.f, 217.f}), //1-end
    make_pair<sf::Vector2f, sf::Vector2f>({237.f, 35.f}, {666.f, 684.f}), //1-1
    make_pair<sf::Vector2f, sf::Vector2f>({237.f, 35.f}, {403.f, 541.f}), //1-2
    make_pair<sf::Vector2f, sf::Vector2f>({237.f, 35.f}, {149.f, 446.f}), //1-3
    make_pair<sf::Vector2f, sf::Vector2f>({237.f, 35.f}, {0.f, 321.f}), //1-4
    make_pair<sf::Vector2f, sf::Vector2f>({237.f, 35.f}, {347.f, 216.f}), //1-5
    make_pair<sf::Vector2f, sf::Vector2f>({367.f, 35.f}, {650.f, 147.f}), //1-6

    //todo сделать лесенку удобнее
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
    //todo 2-nd lvl objects

//    make_pair<sf::Vector2f, sf::Vector2f>({0.f, 0.f}, {0.f, 0.f}), //todo
//    make_pair<sf::Vector2f, sf::Vector2f>({0.f, 0.f}, {0.f, 0.f}), //todo
//    make_pair<sf::Vector2f, sf::Vector2f>({0.f, 0.f}, {0.f, 0.f}), //todo
//    make_pair<sf::Vector2f, sf::Vector2f>({0.f, 0.f}, {0.f, 0.f}), //todo
//    make_pair<sf::Vector2f, sf::Vector2f>({0.f, 0.f}, {0.f, 0.f}), //todo
};

void initGameMap() {
    for (auto obj : mapObjParams) {
        initMapObj({obj.first.x, obj.first.y}, {obj.second.x, obj.second.y});
    }
}

void checkKnyazFalling() {
    bool falling = true;
    for (auto entity : mapObjs) {
        bool a = knyaz.getRight() > entity.getLeft() && knyaz.getRight() < entity.getRight();
        bool b = knyaz.getLeft() > entity.getLeft() && knyaz.getLeft() < entity.getRight();
        bool c = abs(knyaz.getBot() - entity.getTop()) < 0.2f;

        if ((a || b) && c) {
            falling = false;
            break;
        }
    }

    if (knyaz.isFalling && !falling) {
        if (!(knyaz.isMovingRight || knyaz.isMovingLeft)) knyaz.changeAnimation(animationContainer["idle"]);
        else knyaz.changeAnimation(animationContainer["run"]);
    }

    if (falling == knyaz.isFalling) return;
    if (falling && !knyaz.isJump) knyaz.changeAnimation(animationContainer["falling"]);
    if (falling) {
        knyaz.isFalling = true;
        knyaz.freeFallingTimer.restart();
    } else {
        knyaz.isFalling = false;
        knyaz.isJump = false;
    }
}


int main() {
    config = initConfig();
    keymap = getKeymap();

    initDepends();
    const sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    const unsigned int SCREEN_WIDTH = desktopMode.width;
    const unsigned int SCREEN_HEIGHT = desktopMode.height;
    window.create(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), config["GAME_NAME"]);

    initVariables();
    playGameMusic();

    std::vector<sf::Text> textToPrint;
    while (window.isOpen()) {
        pollEvents();
        update(textToPrint);
        redrawFrame(textToPrint);
    }
    return 0;
}

void initDepends() {
    initGameMusic();
    initFont();
    initBGTexture();
    initAnimationTextures();
    initGameMap();
    initAnimations();
    knyaz.animationData = animationContainer["idle"];
}

void initVariables() {
    knyaz.body = getKnyazBody();
    updateBGSprite();
    mainMenu = getMainMenu();
    settingsMenu = getSettingsMenu();
}

void update(std::vector<sf::Text>& textToPrint) {
    constexpr float LOADING_DURATION = 5.f;

    if (curState == GameState::MAIN_MENU) {
        textToPrint = {mainMenu.startText, mainMenu.settingsText, mainMenu.exitText};
    } else if (curState == GameState::HELP_MENU) {
        textToPrint = settingsMenu;
    } else if (curState == GameState::LOAD_SCREEN_1) {
        if (globalTimer.getElapsedTime().asSeconds() >= LOADING_DURATION) {
            curState = GameState::LOAD_SCREEN_2;
            updateBGSprite();
        }
    } else if (curState == GameState::GAME_PROCESS) {
        float elapsedTime = globalTimer.getElapsedTime().asSeconds();
        globalTimer.restart();
        checkKnyazFalling();
        knyazMove(elapsedTime);
        knyaz.animationProcess();
    }
}

void redrawFrame(const std::vector<sf::Text>& textToPrint) {
    window.clear();
    window.draw(BGSprite);

    switch (curState) {
        case GameState::MAIN_MENU:
        case GameState::HELP_MENU:
            for (const sf::Text& text : textToPrint) {
                window.draw(text);
            }
            break;
        case GameState::GAME_PROCESS:
            window.draw(knyaz.body);
            for (const auto& obj : mapObjs) {
                window.draw(obj.body);
            }
            break;
        default:
            break;
    }

    window.display();
}

void pollEvents() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        switch (curState) {
            case GameState::MAIN_MENU:
                MainMenuEventsHandler(event);
                break;
            case GameState::HELP_MENU:
                HelpMenuEventsHandler(event);
                break;
            case GameState::LOAD_SCREEN_2:
                LoadScreenEventsHandler(event);
                break;
            case GameState::GAME_PROCESS:
                GameProcessEventsHandler(event);
                break;
            case GameState::GAME_END:
                GameEndEventsHandler(event);
                break;
        }
    }
}