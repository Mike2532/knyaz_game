#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include "../../../../../config/config.h"

sf::SoundBuffer winBuffer;
sf::Sound winSound;

void initKnyazWinSound() {
    winBuffer.loadFromFile(config["WINNER_FX_FOLDER"] + config["WINNER_FX_SOUND"]);
    winSound.setBuffer(winBuffer);
    winSound.setVolume(17);
}

void startKnyazWinSound() {
    winSound.play();
}
