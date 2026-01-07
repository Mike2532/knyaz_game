#include <SFML/Audio/Music.hpp>
#include <algorithm>
#include "../../../../../config/config.h"
#include "../utils/FX.h"

using namespace std;

FXContainer airContaiter;

void initAirSounds() {
    for (int i = 1; i <= 8; i++) {
        auto newFx = make_unique<FXEffect>();
        newFx->init(config["STRIKES_AIR_FOLDER"] + config["STRIKE_AIR_" + to_string(i)]);
        airContaiter.container.emplace_back(move(newFx));
    }
}

void playRandomAirSound() {
    airContaiter.playRandom();
}

//======

FXContainer armorContaiter;

void initArmorSounds() {
    for (int i = 1; i <= 4; i++) {
        auto newFx = make_unique<FXEffect>();
        newFx->init(config["STRIKES_ARMOR_FOLDER"] + config["STRIKE_ARMOR_" + to_string(i)]);
        armorContaiter.container.emplace_back(move(newFx));
    }
}

void playRandomArmorSound() {
    armorContaiter.playRandom();
}

//====

FXContainer flashContainer;

void initFlashSounds() {
    for (int i = 1; i <= 5; i++) {
        auto newFx = make_unique<FXEffect>();
        newFx->init(config["STRIKES_FLASH_FOLDER"] + config["STRIKE_FLASH_" + to_string(i)]);
        flashContainer.container.emplace_back(move(newFx));
    }
}

void playRandomFlashSound() {
    flashContainer.playRandom();
}