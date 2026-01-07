#include <SFML/Audio/Music.hpp>
#include <vector>
#include "../../../../../config/config.h"
#include <algorithm>
#include <iostream>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <filesystem>

using namespace std;

struct FXEffect {
    sf::SoundBuffer buffer;
    sf::Sound sound;

    void init(string addres) {
        bool ok = buffer.loadFromFile(addres);
        if (!ok) {
            std::cerr << "FAILED TO LOAD SOUND: " << addres << std::endl;
        }
        sound.setBuffer(buffer);
    }

    void play() {
        sound.stop();
        sound.play();
    }
};

struct FXContainer {
    vector<unique_ptr<FXEffect>> container;

    void playRandom() {
        int soindInd = rand() % container.size();
        container[soindInd]->play();
    }
};


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