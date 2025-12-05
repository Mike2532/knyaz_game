#ifndef KNYAZ_GAME_GLOBALS_H
#define KNYAZ_GAME_GLOBALS_H

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <vector>
#include "../types.h"

using namespace std;

extern sf::Texture MainMenuTexture;
extern sf::Texture HelpMenuTexture;
extern sf::Texture LoadScreenOneTexture;
extern sf::Texture LoadScreenTwoTexture;
extern sf::Texture GameProcessTexture;
extern sf::Texture GameEndTexture;

extern sf::Texture KnyazIdleTexture;
extern sf::Texture KnyazRunTexture;
extern sf::Texture KnyazJumpTexture;
extern sf::Texture KnyazFallingTexture;
extern sf::Texture KnyazEasyAttackTexture;
extern sf::Texture KnyazHeavyAttackTexture;
extern sf::Texture KnyazDeathTexture;
extern sf::Texture KnyazWallHangTexture;

extern sf::Texture GroundTexture;
extern sf::Texture LavaTexture;
extern sf::Texture SpikesTexture;
extern sf::Texture SpikesUpTexture;

extern sf::Music GameMusic;
extern sf::Font myFont;
extern sf::Sprite BGSprite;

struct AnimationData {
    sf::Texture animationTexture;
    int animationFrames;
    AnimationTypes animationType;
};

extern std::map<std::string, AnimationData> animationContainer;

struct Knyaz : GameEntity {
    bool isMovingLeft = false;
    bool isMovingRight = false;
    bool isJump = false;
    bool isFalling = false;
    bool isDoubleJump = false;
    bool isLeftOrented = false;
    bool isAlive = true;
    bool isClimbing = false;

    int animationFrameNumber;

    sf::Clock freeFallingTimer;
    sf::Clock animationTimer;

    AnimationData animationData;

    void textureUpdate() {
        constexpr int STRIP_FRAME_OFFSET = 120;
        constexpr int NORMAL_BASE_X = 27;
        constexpr int ATTACK_BASE_X = 40;
        constexpr int LEFT_ORIENTED_EXTRA = 43;
        constexpr int LEFT_ATTACK_EXTRA = 65;

        constexpr int NORMAL_W = 43;
        constexpr int NORMAL_H = 40;
        constexpr int ATTACK_W = 65;
        constexpr int ATTACK_H = 45;

        constexpr int NORMAL_TOP = 40;
        constexpr int ATTACK_TOP = 35;

        constexpr float KNYAZ_SIDE_SIZE = 80.f;

        body.setTexture(&animationData.animationTexture);

        if (isLeftOrented) {
            if (animationData.animationType == AnimationTypes::ATTACK) {
                body.setTextureRect(sf::IntRect(
                        STRIP_FRAME_OFFSET * animationFrameNumber + ATTACK_BASE_X + LEFT_ATTACK_EXTRA,
                        ATTACK_TOP,
                        -ATTACK_W,
                        ATTACK_H
                ));

                if (animationFrameNumber == animationData.animationFrames - 1) {
                    if (isAlive) changeAnimation(animationContainer["idle"]);
                    body.setTextureRect(sf::IntRect(
                            STRIP_FRAME_OFFSET * animationFrameNumber + NORMAL_BASE_X + LEFT_ORIENTED_EXTRA,
                            NORMAL_TOP,
                            -NORMAL_W,
                            NORMAL_H
                    ));
                }
            } else {
                body.setTextureRect(sf::IntRect(
                        STRIP_FRAME_OFFSET * animationFrameNumber + NORMAL_BASE_X + LEFT_ORIENTED_EXTRA,
                        NORMAL_TOP,
                        -NORMAL_W,
                        NORMAL_H
                ));
            }
        } else {
            if (animationData.animationType == AnimationTypes::ATTACK) {
                body.setTextureRect(sf::IntRect(
                        STRIP_FRAME_OFFSET * animationFrameNumber + ATTACK_BASE_X,
                        ATTACK_TOP,
                        ATTACK_W,
                        ATTACK_H
                ));

                if (animationFrameNumber == animationData.animationFrames - 1) {
                    if (isAlive) changeAnimation(animationContainer["idle"]);
                    body.setTextureRect(sf::IntRect(
                            STRIP_FRAME_OFFSET * animationFrameNumber + NORMAL_BASE_X,
                            NORMAL_TOP,
                            NORMAL_W,
                            NORMAL_H
                    ));
                }
            } else {
                body.setTextureRect(sf::IntRect(
                        STRIP_FRAME_OFFSET * animationFrameNumber + NORMAL_BASE_X,
                        NORMAL_TOP,
                        NORMAL_W,
                        NORMAL_H
                ));
            }
        }

        body.setSize(sf::Vector2f(KNYAZ_SIDE_SIZE, KNYAZ_SIDE_SIZE));
    }


    void animationProcess() {
        constexpr int ANIMATION_DURATON = 100;

        if (
                animationTimer.getElapsedTime().asMilliseconds() < ANIMATION_DURATON ||
                !isAlive && animationFrameNumber == animationData.animationFrames - 1
        ) return;
        animationTimer.restart();

        animationFrameNumber++;
        animationFrameNumber %= animationData.animationFrames;

        textureUpdate();
    }

    void changeAnimation(const AnimationData& newAnimation) {
        if (!isAlive) return;
        animationData = newAnimation;
        animationFrameNumber = 0;
        animationTimer.restart();
        textureUpdate();
    }
};

extern Knyaz knyaz;
extern MainMenu mainMenu;
extern SettingsMenu settingsMenu;
extern sf::RenderWindow window;
extern GameState curState;
extern std::map<std::string, std::string> config;
extern std::map<std::string, sf::Keyboard::Scancode> keymap;
extern sf::Clock globalTimer;

void initDepends();
void initVariables();

void initGameMap();

extern vector<GameEntity> mapObjs;

#endif //KNYAZ_GAME_GLOBALS_H
