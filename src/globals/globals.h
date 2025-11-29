#ifndef KNYAZ_GAME_GLOBALS_H
#define KNYAZ_GAME_GLOBALS_H

#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include "../types.h"

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
    bool isLeftOrented = false;

    int animationFrameNumber;

    sf::Clock freeFallingTimer;
    sf::Clock animationTimer;

    AnimationData animationData;

    void textureUpdate() {
        body.setTexture(&animationData.animationTexture);
        if (isLeftOrented) {
            if (animationData.animationType == AnimationTypes::ATTACK) {
                body.setTextureRect(sf::IntRect(120 * animationFrameNumber + 40 + 65, 35, -65, 45));
                if (animationFrameNumber == animationData.animationFrames - 1) {
                    changeAnimation(animationContainer["idle"]);
                    body.setTextureRect(sf::IntRect(120 * animationFrameNumber + 27 + 43, 40, -43, 40));
                }
            } else {
                body.setTextureRect(sf::IntRect(120 * animationFrameNumber + 27 + 43, 40, -43, 40));
            }
        } else {
            if (animationData.animationType == AnimationTypes::ATTACK) {
                body.setTextureRect(sf::IntRect(120 * animationFrameNumber + 40, 35, 65, 45));
                if (animationFrameNumber == animationData.animationFrames - 1) {
                    changeAnimation(animationContainer["idle"]);
                    body.setTextureRect(sf::IntRect(120 * animationFrameNumber + 27, 40, 43, 40));
                }
            } else {
                body.setTextureRect(sf::IntRect(120 * animationFrameNumber + 27, 40, 43, 40));
            }
        }
        body.setSize(sf::Vector2f(80.f, 80.f));
    }

    void animationProcess() {
        if (animationTimer.getElapsedTime().asMilliseconds() < 100) return;
        animationTimer.restart();

        animationFrameNumber++;
        animationFrameNumber %= animationData.animationFrames;

        textureUpdate();
    }

    void changeAnimation(const AnimationData& newAnimation) {
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

#endif //KNYAZ_GAME_GLOBALS_H
