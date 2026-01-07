#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "../../../../../config/config.h"

sf::SoundBuffer runBuffer;
sf::Sound runSound;

void initKnyazRunSound() {
    runBuffer.loadFromFile(config["KNYAZ_RUN_FOLDER"] + config["KNYAZ_RUN_SOUND"]);
    runSound.setBuffer(runBuffer);
    runSound.setVolume(17);
}

void startKnyazRunSound() {
    runSound.play();
}

void stopKnyazRunSound() {
    runSound.stop();
}