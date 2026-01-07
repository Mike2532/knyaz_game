#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "../../../../../config/config.h"

sf::SoundBuffer tpBuffer;
sf::Sound tpSound;

void initTpSound() {
    tpBuffer.loadFromFile(config["TP_SOUND_FOLDER"] + config["TP_SOUND"]);
    tpSound.setBuffer(tpBuffer);
    tpSound.setVolume(20);
}

void playTpSound() {
    tpSound.play();
}
