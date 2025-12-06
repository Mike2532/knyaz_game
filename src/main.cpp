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

//    Enemy myEnemy;
//    myEnemy.body.setSize({80.f, 80.f});
//    myEnemy.body.setPosition({1932.f - 1774.f, 691.f});
//    myEnemy.body.setFillColor(sf::Color::Red);
//    myEnemy.LEFT_ACTIVE_EDGE = 1774.f - 1774.f;
//    myEnemy.LEFT_PATROLING_EDGE = 1899.f - 1774.f;
//    myEnemy.RIGHT_PATROLING_EDGE = 2290.f - 1774.f - 300.f;
//    myEnemy.RIGHT_ACTIVE_EDGE = 2420.f - 1774.f  - 300.f;
//    mapEnemys.push_back(myEnemy);

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
    initAnimations();
    initObjsTextures();
    initGameMap();
    initEnemys();
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

        for (auto &enemy : mapEnemys) {
            enemy.checkKnyazVision();
            enemy.move(elapsedTime);
        }

        knyazMove(elapsedTime);
        checkKnyazFalling();
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

            for (auto &enemy : mapEnemys) {
                window.draw(enemy.body);
            }

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