#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "../../../../../config/config.h"

sf::SoundBuffer rageBuffer;
sf::Sound rageSound;

void initRageSound() {
    rageBuffer.loadFromFile(config["RAGE_SOUND_FOLDER"] + config["RAGE_SOUND"]);
    rageSound.setBuffer(rageBuffer);
    rageSound.setVolume(30);
}

void playRageSound() {
    rageSound.play();
}
