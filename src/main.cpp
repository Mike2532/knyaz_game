#include <iostream>
#include <vector>
#include "globals/globals.h"
#include "types.h"
#include "../../config/config.h"
#include "./ui/helpMenu/helpMenu.h"
#include "./ui/loadScreen/loadScreen.h"
#include "./knyaz/eventsHandler/eventsHandler.h"
#include "./ui/gameEnd/gameEnd.h"
#include "./ui/utils/deathEnemys.h"
#include "./resources/font/font.h"
#include "./resources/sounds/gameMusic/music.h"
#include "./resources/BG/BG.h"
#include "./resources/animations/animations.h"
#include "./resources/objs/objs.h"
#include "./resources/ui/ui.h"
#include "./knyaz/move/move.h"
#include "./knyaz/move/falling/falling.h"
#include "./knyaz/move/collisionChecker/checker.h"
#include "./knyaz/state/state.h"
#include "./globals/mapObjs/mapObjs.h"
#include "./globals/mapPortals/mapPortals.h"
#include "./knyaz.h"
#include "./globals/mapEnemys/mapEnemys.h"

using namespace std;

extern map<string, sf::Keyboard::Scancode> getKeymap();

void pollEvents();
void update(vector<sf::Text>& textToPrint);
void redrawFrame(const vector<sf::Text>& textToPrint);

int main() {
    config = initConfig();
    keymap = getKeymap();

    initDepends();
    const sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    const unsigned int SCREEN_WIDTH = desktopMode.width;
    const unsigned int SCREEN_HEIGHT = desktopMode.height;

    cout << SCREEN_WIDTH << ' ' << SCREEN_HEIGHT << endl;

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
    initAnimations();
    initObjsTextures();
    initUITextures();
    initGameMap();
    initEnemys();
    initMapPortals();
    initAntiGravityField();
    initUI();
    knyaz.animationData = animationContainer["idle"];
    HpIndicatorSprite.setTexture(HpIndicatorTexture);
    srand(time(NULL));
}

void initVariables() {
    knyaz.body = initKnyazBody();
    updateBGSprite();
    mainMenu = getMainMenu();
    helpMenu = getHelpMenu();
}

void update(std::vector<sf::Text>& textToPrint) {
    constexpr float LOADING_DURATION = 5.f;

    if (curState == GameState::MAIN_MENU) {
        textToPrint = {mainMenu.startText, mainMenu.settingsText, mainMenu.exitText};
    } else if (curState == GameState::HELP_MENU) {
        textToPrint = helpMenu;
    } else if (curState == GameState::LOAD_SCREEN_1) {
        if (globalTimer.getElapsedTime().asSeconds() >= LOADING_DURATION) {
            curState = GameState::LOAD_SCREEN_2;
            updateBGSprite();
        }
    } else if (curState == GameState::GAME_PROCESS) {
        float elapsedTime = globalTimer.getElapsedTime().asSeconds();
        globalTimer.restart();

        for (auto &enemy : mapEnemys) {
            enemy.stunProcess();
            enemy.checkKnyazVision();
            enemy.move(elapsedTime);
            enemy.tryToAttack();
            enemy.animationProcess();
            enemy.spritePositionUpdate();
        }

        checkKnyazPortaling();
        knyazMove(elapsedTime);
        checkKnyazFalling();
        checkKnyazEnemyCollision();
        enemysTakenDamage();
        removeDeathEnemys();
        knyaz.animationProcess();
        knyaz.spritePositionUpdate();
        knyaz.takeDamage();
        updateHpIndicator();
        updateUI();
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
            window.draw(knyaz.objSprite);

            for (auto &enemy : mapEnemys) {
                window.draw(enemy.objSprite);
            }

            for (const auto& obj : mapObjs) {
                window.draw(obj.body);
            }

            if (!lastTeleported) {
                window.draw(antiGravityField);
                for (const auto& portal : mapPortals) {
                    window.draw(portal.inBody);
                    window.draw(portal.outBody);
                }
            }

            window.draw(HpIndicatorSprite);

            window.draw(ui.focusOutline);
            window.draw(ui.focusFill);
            window.draw(ui.rageOutline);
            window.draw(ui.rageFill);

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
                mainMenuEventsHandler(event);
                break;
            case GameState::HELP_MENU:
                helpMenuEventsHandler(event);
                break;
            case GameState::LOAD_SCREEN_2:
                LoadScreenEventsHandler(event);
                break;
            case GameState::GAME_PROCESS:
                knyazEventsHandler(event);
                break;
            case GameState::GAME_END:
                GameEndEventsHandler(event);
                break;
        }
    }
}

//todo подумать над ценностью
// сейчас много всего намешено - и flow и князь Владимир и порталы
//
// todo не стоит отдельно упоминать папку globals
// todo баг на широком экране - попыл задник и UI
// todo анимации при телепортации чтобы это было явно, а не выглядело как баг