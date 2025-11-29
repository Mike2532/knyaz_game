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

extern sf::Texture GroundTexture;

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
        constexpr int DISTANSE_OFFSET = 120;
        constexpr int RIGHT_INNER_OFFSET = 27;
        constexpr int ATTACK_OFFSET = 40;
        constexpr int LEFT_ATTACK_OFFSET = 65;
        constexpr int ATTACK_TOP = 35;
        constexpr int TOP = 40;
        constexpr int ATTACK_HEIGHT = 40;
        constexpr int HEIGHT = 40;
        constexpr int ATTACK_WIDTH = 43;
        constexpr int WIDTH = 43;
        constexpr int LEFT_ORENTED_OFFSET = 43;
        constexpr float KNYAZ_SIDE_SIZE = 80.f;

        body.setTexture(&animationData.animationTexture);
        if (isLeftOrented) {
            if (animationData.animationType == AnimationTypes::ATTACK) {
                body.setTextureRect(sf::IntRect(DISTANSE_OFFSET * animationFrameNumber + ATTACK_OFFSET + LEFT_ATTACK_OFFSET, ATTACK_TOP, -ATTACK_WIDTH, ATTACK_HEIGHT));
                if (animationFrameNumber == animationData.animationFrames - 1) {
                    changeAnimation(animationContainer["idle"]);
                    body.setTextureRect(sf::IntRect(DISTANSE_OFFSET * animationFrameNumber + RIGHT_INNER_OFFSET + LEFT_ORENTED_OFFSET, TOP, -WIDTH, HEIGHT));
                }
            } else {
                body.setTextureRect(sf::IntRect(DISTANSE_OFFSET * animationFrameNumber + RIGHT_INNER_OFFSET + LEFT_ORENTED_OFFSET, TOP, -WIDTH, HEIGHT));
            }
        } else {
            if (animationData.animationType == AnimationTypes::ATTACK) {
                body.setTextureRect(sf::IntRect(DISTANSE_OFFSET * animationFrameNumber + ATTACK_OFFSET, ATTACK_TOP, ATTACK_WIDTH, ATTACK_HEIGHT));
                if (animationFrameNumber == animationData.animationFrames - 1) {
                    changeAnimation(animationContainer["idle"]);
                    body.setTextureRect(sf::IntRect(DISTANSE_OFFSET * animationFrameNumber + RIGHT_INNER_OFFSET, TOP, WIDTH, HEIGHT));
                }
            } else {
                body.setTextureRect(sf::IntRect(DISTANSE_OFFSET * animationFrameNumber + RIGHT_INNER_OFFSET, TOP, WIDTH, HEIGHT));
            }
        }
        body.setSize(sf::Vector2f(KNYAZ_SIDE_SIZE, KNYAZ_SIDE_SIZE));
    }

    void animationProcess() {
        constexpr int ANIMATION_DURATON = 100;

        if (animationTimer.getElapsedTime().asMilliseconds() < ANIMATION_DURATON) return;
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

void initGameMap();

extern vector<GameEntity> mapObjs;

#endif //KNYAZ_GAME_GLOBALS_H
