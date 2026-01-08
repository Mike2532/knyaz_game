#include <iostream>
#include <vector>
#include <cmath>
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
#include "./globals/tpEntity/tpEntity.h"
#include "./resources/sounds/fx/fight/fight.h"
#include "./resources/sounds/fx/run/knyazRunFX.h"
#include "./resources/sounds/fx/landing/knyazLandingFX.h"
#include "./resources/sounds/fx/wind/wind.h"
#include "./resources/sounds/fx/bottle/bottle.h"
#include "./resources/sounds/fx/tp/tp.h"
#include "./resources/sounds/fx/rage/rage.h"
#include "./globals/viewport/viewport.h"

using namespace std;

extern map<string, sf::Keyboard::Scancode> getKeymap();

void pollEvents();
void update(vector<sf::Text>& textToPrint);
void redrawFrame(const vector<sf::Text>& textToPrint);

int main() {
    config = initConfig();
    keymap = getKeymap();

    initDepends();

    cout << SCREEN_WIDTH << ' ' << SCREEN_HEIGHT << endl;
    cout << LOGICAL_W << ' ' << LOGICAL_H << endl;
    cout << VIEW_SCALE_X << ' ' << VIEW_SCALE_Y << endl;

    window.create(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), config["GAME_NAME"]);

    initVariables();
    playGameMusic();

    std::vector<sf::Text> textToPrint;

    sf::View view;
    view.setSize(LOGICAL_W, LOGICAL_H);
    view.setCenter(LOGICAL_W / 2, LOGICAL_H / 2);
    window.setView(view);

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
    initGameMap(VIEW_SCALE);
    initEnemys();
    initMapPortals();
    initAntiGravityField();
    initUI(make_pair(LOGICAL_W, LOGICAL_H));
    initAirSounds();
    initArmorSounds();
    initFlashSounds();
    initKnyazRunSound();
    initKnyazLandingSound();
    initWindSounds();
    initBottleSound();
    initTpSound();
    initRageSound();
    knyaz.animationData = animationContainer["idle"];
    HpIndicatorSprite.setTexture(HpIndicatorTexture);
    HpIndicatorSprite.setScale({VIEW_SCALE_X, VIEW_SCALE_Y});
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
        knyaz.tpProcess();
        updateHpIndicator();
        updateUI();
    }
}

void drawBG() {
    const float relY = static_cast<float>(LOGICAL_H) / static_cast<float>(BG_HEIGHT);
    BGSprite.setScale({1, relY});

    const float relX = static_cast<float>(LOGICAL_W) / static_cast<float>(BG_WIDTH);
    const int screens = static_cast<int>(ceil(relX));
    for (int i = 0; i < screens; i++) {
        const float bgPos = i * BG_WIDTH;
        BGSprite.setPosition({bgPos, 0});
        window.draw(BGSprite);
    }
}

void drawUI() {
    window.draw(ui.focusOutline);
    window.draw(ui.focusFill);
    window.draw(ui.rageOutline);
    window.draw(ui.rageFill);
}

void redrawFrame(const std::vector<sf::Text>& textToPrint) {
    window.clear();
    drawBG();

    switch (curState) {
        case GameState::MAIN_MENU:
        case GameState::HELP_MENU:
            for (const sf::Text& text : textToPrint) {
                window.draw(text);
            }
            break;
        case GameState::GAME_PROCESS:
            window.draw(knyaz.body);
            window.draw(knyaz.objSprite);

            for (auto &enemy : mapEnemys) {
                window.draw(enemy.body);
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

            drawUI();

            for (auto& e : tpEntityArr) {
                window.draw(e.objSprite);
                e.animationProcess();
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