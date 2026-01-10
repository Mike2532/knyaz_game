#include <vector>
#include <cmath>
#include "globals/globals.h"
#include "types.h"
#include "../../config/config.h"
#include "./ui/helpMenu/helpMenu.h"
#include "./resources/font/font.h"
#include "./resources/sounds/gameMusic/music.h"
#include "./resources/BG/BG.h"
#include "./resources/animations/animations.h"
#include "./resources/objs/objs.h"
#include "./resources/ui/ui.h"
#include "./knyaz/state/state.h"
#include "./globals/mapObjs/mapObjs.h"
#include "./globals/mapPortals/mapPortals.h"
#include "./knyaz.h"
#include "./globals/mapEnemys/mapEnemys.h"
#include "./resources/sounds/fx/fight/fight.h"
#include "./resources/sounds/fx/run/knyazRunFX.h"
#include "./resources/sounds/fx/landing/knyazLandingFX.h"
#include "./resources/sounds/fx/wind/wind.h"
#include "./resources/sounds/fx/bottle/bottleFX.h"
#include "./resources/sounds/fx/tp/tp.h"
#include "./resources/sounds/fx/rage/rage.h"
#include "./resources/animations/boss/boss.h"
#include "globals/bottle/bottle.h"
#include "./resources/sounds/fx/win/win.h"
#include "../ui/utils/scaleToScreen.h"
#include "./kernel/polling/eventsPolling.h"
#include "./kernel/drawer/redraw.h"
#include "./kernel/updater/update.h"

using namespace std;

extern map<string, sf::Keyboard::Scancode> getKeymap();

void initDepends();
void initVariables();

const sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
const unsigned int SCREEN_WIDTH = desktopMode.width;
const unsigned int SCREEN_HEIGHT = desktopMode.height;

int main() {
    config = initConfig();
    keymap = getKeymap();

    initDepends();

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

void initBaseSystems() {
    initGameMusic();
    initFont();
    srand(time(nullptr));
}

void initAllTextures() {
    initBGTexture();
    initAnimationTextures();
    initBossTextures();
    initObjsTextures();
    initUITextures();

    HpIndicatorSprite.setTexture(HpIndicatorTexture);
}

void initAllAnimations() {
    initAnimations();
}

void initWorld() {
    initGameMap();
}

void initWorldEntities() {
    initEnemys();
    initMapPortals();
    initAntiGravityField();
    spawnBossBottles();
}

void initGameUI() {
    initUI({SCREEN_WIDTH, SCREEN_HEIGHT});
}

void initAllSounds() {
    initAirSounds();
    initArmorSounds();
    initFlashSounds();
    initKnyazRunSound();
    initKnyazLandingSound();
    initWindSounds();
    initBottleSound();
    initTpSound();
    initRageSound();
    initKnyazWinSound();
}

void initDepends() {
    initBaseSystems();
    initAllTextures();
    initAllAnimations();
    initWorld();
    initWorldEntities();
    initGameUI();
    initAllSounds();
}


void initVariables() {
    knyaz.body = initKnyazBody();
    knyaz.animationData = animationContainer["idle"];
    updateBGSprite();
    mainMenu = getMainMenu();
    helpMenu = getHelpMenu();
}