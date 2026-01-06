#include <iostream>
#include <SFML/Audio/Music.hpp>
#include "../../../../config/config.h"

sf::Music GameMusic;

void initGameMusic() {
    if (!GameMusic.openFromFile(config["MUSIC_FOLDER"] + config["GAME_MUSIC_FILE"])) {
        std::cerr << "Failed to open music file\n";
    } else {
        GameMusic.setVolume(5);
        GameMusic.setLoop(true);
    }
}

void playGameMusic() {
    GameMusic.play();
}