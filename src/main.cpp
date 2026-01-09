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

using namespace std;

extern map<string, sf::Keyboard::Scancode> getKeymap();

void pollEvents();
void update(vector<sf::Text>& textToPrint);
void redrawFrame(const vector<sf::Text>& textToPrint);
void scaleToScreen();

const sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
const unsigned int SCREEN_WIDTH = desktopMode.width;
const unsigned int SCREEN_HEIGHT = desktopMode.height;

const unsigned int BG_WIDTH = 1097;
const unsigned int BG_HEIGHT = 900;

int main() {
    config = initConfig();
    keymap = getKeymap();

    initDepends();

    cout << SCREEN_WIDTH << ' ' << SCREEN_HEIGHT << endl;
    cout << "hello world\n";

    window.create(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), config["GAME_NAME"]);
    scaleToScreen();

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
    initUI(make_pair(SCREEN_WIDTH, SCREEN_HEIGHT));
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
            enemy.easyComboReversal();
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
    constexpr float LOGIC_W = 1440;
    constexpr float LOGIC_H = 900;

    float bgScale = LOGIC_H / BG_HEIGHT;
    float bgWidth = BG_WIDTH * bgScale;

    int numCopies = static_cast<int>(ceil(LOGIC_W / bgWidth)) + 1;

    BGSprite.setScale(bgScale, bgScale);

    for (int i = 0; i < numCopies; i++) {
        BGSprite.setPosition(i * bgWidth, 0);
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

    window.setView(UIView);
    drawBG();

    window.setView(gameView);
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
                for (int i = 0; i < 2; i++) {
                    window.draw(mapPortals[i].inBody);
                    window.draw(mapPortals[i].outBody);
                }
            }

            if (!superLastTeleported) {
                window.draw(mapPortals[2].inBody);
                window.draw(mapPortals[2].outBody);
            }

            for (auto& e : tpEntityArr) {
                window.draw(e.objSprite);
                e.animationProcess();
            }

            window.setView(UIView);
            window.draw(HpIndicatorSprite);

            drawUI();

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

void scaleToScreen() {
    constexpr float LOGIC_W = 1440;
    constexpr float LOGIC_H = 900;

    float windowWidth = SCREEN_WIDTH;
    float windowHeight = SCREEN_HEIGHT;

    gameView.setSize(LOGIC_W, LOGIC_H);
    gameView.setCenter(LOGIC_W / 2.f, LOGIC_H / 2.f);

    float aspectRatio = LOGIC_W / LOGIC_H;
    float windowAspectRatio = windowWidth / windowHeight;

    float vpX = 0.0f;
    float vpY = 0.0f;
    float vpWidth = 1.0f;
    float vpHeight = 1.0f;

    if (windowAspectRatio > aspectRatio) {
        vpHeight = aspectRatio / windowAspectRatio;
        vpY = (1.0f - vpHeight) / 2.0f;
    } else {
        vpWidth = windowAspectRatio / aspectRatio;
        vpX = (1.0f - vpWidth) / 2.0f;
    }

    gameView.setViewport(sf::FloatRect(vpX, vpY, vpWidth, vpHeight));

    UIView.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    UIView.setCenter(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);
    UIView.setViewport({0.f, 0.f, 1.f, 1.f});

    window.setView(gameView);
}

//todo подумать над ценностью
// сейчас много всего намешено - и flow и князь Владимир и порталы
//
// todo не стоит отдельно упоминать папку globals
// todo баг на широком экране - попыл задник и UI
// todo анимации при телепортации чтобы это было явно, а не выглядело как баг