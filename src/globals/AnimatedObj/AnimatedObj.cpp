#include "./AnimatedObj.h"

void AnimatedObj::animationProcess() {
    constexpr int ANIMATION_DURATON = 100;

    if (
            animationTimer.getElapsedTime().asMilliseconds() < ANIMATION_DURATON ||
            !isAlive && animationFrameNumber == animationData.animationFrames - 1
            ) return;
    animationTimer.restart();

    if (!(animationFrameNumber == 0 && isStunned)) {
        animationFrameNumber++;
        animationFrameNumber %= animationData.animationFrames;
    }

    textureUpdate();
}

void AnimatedObj::changeAnimation(const AnimationData& newAnimation) {
    if (!isAlive) return;
    animationData = newAnimation;
    animationFrameNumber = 0;
    animationTimer.restart();
    textureUpdate();
}