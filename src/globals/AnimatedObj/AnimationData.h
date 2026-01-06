#ifndef KNYAZ_GAME_ANIMATIONDATA_H
#define KNYAZ_GAME_ANIMATIONDATA_H

#include <SFML/Graphics/Texture.hpp>
#include "../../types.h"

struct AnimationData {
    sf::Texture animationTexture;
    int animationFrames;
    AnimationTypes animationType;
};

#endif //KNYAZ_GAME_ANIMATIONDATA_H
