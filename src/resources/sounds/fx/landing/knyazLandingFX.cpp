#include <SFML/Audio/Music.hpp>
#include <algorithm>
#include "../utils/FX.h"
#include "../../../../../config/config.h"

using namespace std;

FXContainer landingContaiter;

void initKnyazLandingSound() {
    for (int i = 1; i <= 2; i++) {
        auto newFx = make_unique<FXEffect>();
        newFx->init(config["KNYAZ_LANDING_FOLDER"] + config["KNYAZ_LANDING_SOUND_" + to_string(i)]);
        landingContaiter.container.emplace_back(move(newFx));
    }
}

void playRandomLandingSound() {
    landingContaiter.playRandom();
}