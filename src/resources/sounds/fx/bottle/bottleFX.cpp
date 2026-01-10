#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "../../../../../config/config.h"

sf::SoundBuffer bottleBuffer;
sf::Sound bottleSound;

void initBottleSound() {
    bottleBuffer.loadFromFile(config["BOTTLE_SOUND_FOLDER"] + config["BOTTLE_SOUND"]);
    bottleSound.setBuffer(bottleBuffer);
    bottleSound.setVolume(17);
}

void playBottleSound() {
    bottleSound.play();
}
