#ifndef KNYAZ_GAME_ANIMATEDOBJ_H
#define KNYAZ_GAME_ANIMATEDOBJ_H

#include "../mapObjs/GameEntity/GameEntity.h"
#include "./AnimationData.h"

struct AnimatedObj : GameEntity {
    sf::Sprite objSprite;

    bool isFalling = false;
    bool isAlive = true;
    bool isLeftOrented = false;
    bool isSpriteLeftOrented = false;

    sf::Clock freeFallingTimer;

    sf::Clock animationTimer;
    AnimationData animationData;
    int animationFrameNumber;

    bool isStunned = false;

    virtual void textureUpdate() = 0;

    void animationProcess();
    void changeAnimation(const AnimationData& newAnimation);
};

#endif //KNYAZ_GAME_ANIMATEDOBJ_H
