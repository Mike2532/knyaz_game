#ifndef KNYAZ_GAME_FX_H
#define KNYAZ_GAME_FX_H

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <iostream>

using namespace std;

struct FXEffect {
    sf::SoundBuffer buffer;
    sf::Sound sound;

    void init(string addres);
    void play();
};

struct FXContainer {
    vector<unique_ptr<FXEffect>> container;

    void playRandom();
    void stopAll();
};

#endif //KNYAZ_GAME_FX_H
