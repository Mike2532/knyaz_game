#include <SFML/Audio/Music.hpp>
#include <algorithm>
#include "../utils/FX.h"
#include "../../../../../config/config.h"

using namespace std;

FXContainer windContaiter;

void initWindSounds() {
    for (int i = 1; i <= 1; i++) {
        auto newFx = make_unique<FXEffect>();
        newFx->init(config["WIND_SOUND_FOLDER"] + config["WIND_SOUND_" + to_string(i)]);
        windContaiter.container.emplace_back(move(newFx));
    }
}

void playRandomWindSound() {
    windContaiter.playRandom();
}

void stopWindSound() {
    windContaiter.stopAll();
}
