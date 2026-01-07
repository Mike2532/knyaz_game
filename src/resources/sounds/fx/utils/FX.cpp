#include "./FX.h"

void FXEffect::init(std::string addres) {
    bool ok = buffer.loadFromFile(addres);
    if (!ok) {
        std::cerr << "FAILED TO LOAD SOUND: " << addres << std::endl;
    }
    sound.setBuffer(buffer);
}

void FXEffect::play() {
    sound.stop();
    sound.play();
}

void FXContainer::playRandom() {
    int soindInd = rand() % container.size();
    container[soindInd]->play();
}

void FXContainer::stopAll() {
    for (auto &s : container) {
        s->sound.stop();
    }
}