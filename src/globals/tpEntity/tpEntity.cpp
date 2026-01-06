#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include "../AnimatedObj/AnimatedObj.h"
#include "./tpEntity.h"
#include "../knyaz/knyaz.h"
#include "../globals/globals.h"
#include <iostream>

using namespace std;

void TpEntity::textureUpdate() {
    if (animationFrameNumber == animationData.animationFrames - 1) {
        objSprite.setPosition(-100, -100);
    }

    constexpr int ANIMATION_WIDTH = 100;
    constexpr int ANIMATION_HEIGHT = 100;

    objSprite.setTexture(animationData.animationTexture);

    objSprite.setTextureRect(sf::IntRect(
            ANIMATION_WIDTH * animationFrameNumber,
            0,
            ANIMATION_WIDTH,
            ANIMATION_HEIGHT
    ));

    float SCALE_X = 1.f;
    float SCALE_Y = 1.f;

    objSprite.setScale(SCALE_X, SCALE_Y);
}

vector<TpEntity> tpEntityArr;

void spawnTpEntity(const sf::Vector2f knyazPos) {
    const sf::Vector2f tpEntityPos = {knyazPos.x - 27, knyazPos.y - 25};

    TpEntity entity;
    entity.animationFrameNumber = 0;
    entity.animationData = animationContainer["tpEntityes"];
    entity.objSprite.setPosition(tpEntityPos);

    tpEntityArr.emplace_back(entity);
}