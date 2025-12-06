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

struct AnimatedObj : GameEntity {
    bool isFalling = false;
    bool isAlive = true;
    sf::Clock freeFallingTimer;

    sf::Clock animationTimer;
    AnimationData animationData;
    int animationFrameNumber;

    virtual void textureUpdate() = 0;

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

struct Knyaz : AnimatedObj {
    bool isMovingLeft = false;
    bool isMovingRight = false;
    bool isJump = false;
    bool isDoubleJump = false;
    bool isLeftOrented = false;
    bool isClimbing = false;

    void textureUpdate() override {
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
};

extern Knyaz knyaz;
extern MainMenu mainMenu;
extern SettingsMenu settingsMenu;
extern sf::RenderWindow window;
extern GameState curState;
extern std::map<std::string, std::string> config;
extern std::map<std::string, sf::Keyboard::Scancode> keymap;
extern sf::Clock globalTimer;

//2 состояния ящера
// патрулирование - ящер ходит вперед назад между заданными x координатами
// агрессия - ящер побежит к князю
// ящер умеет только ходить и атаковать
// ящер знает границы потрулирования и границы своего мира - куда он не пойдет дальше даже во время боя
//
//todo в отрисовщике хранить не сами объекты, а указатели на них
//тогда можно тело ящера запихнуть и в глобальную карту и в структуру ящера
struct Enemy : AnimatedObj {
    float LEFT_PATROLING_EDGE;
    float RIGHT_PATROLING_EDGE;
    float LEFT_ACTIVE_EDGE;
    float RIGHT_ACTIVE_EDGE;


    bool seeKnyaz = false;
    bool isPatrolingLeft = true;

    sf::Clock searchingTimer;
    EnemyStates state = EnemyStates::PATROLLING;

    void move(const float& elapsedTime) {
        float PATROL_SPEED = 150.f;
        float AGRESSIVE_SPEED = 200.f;
        sf::Vector2f enemyPos = body.getPosition();

        if (state == EnemyStates::PATROLLING) {
            if (isPatrolingLeft) {
                if (enemyPos.x > LEFT_PATROLING_EDGE) {
                    enemyPos.x -= PATROL_SPEED * elapsedTime;
                    body.setPosition(enemyPos);
                } else {
                    isPatrolingLeft = false;
                }
            } else {
                if (enemyPos.x < RIGHT_PATROLING_EDGE) {
                    enemyPos.x += PATROL_SPEED * elapsedTime;
                    body.setPosition(enemyPos);
                } else {
                    isPatrolingLeft = true;
                }
            }
        } else if (state == EnemyStates::AGRESSIVE && seeKnyaz) {
            constexpr int NOT_NEED_TO_RUN_DISTANSE = 2;

            float enemyLeft = getLeft();
            float enemyRight = getRight();
            float knyazLeft = knyaz.getLeft();
            float knyazRight = knyaz.getRight();

            bool isKnyazLeft = knyazRight <= enemyLeft;
            bool needToLeftRun = enemyLeft - knyazRight >= NOT_NEED_TO_RUN_DISTANSE;

            bool isKnyazRight = knyazLeft >= enemyRight;
            bool needToRightRun = knyazLeft - enemyRight >= NOT_NEED_TO_RUN_DISTANSE;

            if (isKnyazLeft && needToLeftRun) {
                enemyPos.x -= AGRESSIVE_SPEED * elapsedTime;
                enemyPos.x = max(enemyPos.x, LEFT_ACTIVE_EDGE);
                body.setPosition(enemyPos);
            } else if (isKnyazRight && needToRightRun) {
                enemyPos.x += AGRESSIVE_SPEED * elapsedTime;
                enemyPos.x = min(enemyPos.x, RIGHT_ACTIVE_EDGE);
                body.setPosition(enemyPos);
            }
        }
    }

    void checkKnyazVision() {
        constexpr float SEARCHING_DURATION = 2.f;
        float enemyBot = getBot();
        if (!knyaz.isFalling) {
            bool a = true;
        }
        bool isKnyazUpperOrLower = knyaz.getTop() >= getBot() || knyaz.getBot() <= getTop();

        if (isKnyazUpperOrLower) {
            if (seeKnyaz) {
                seeKnyaz = false;
                searchingTimer.restart();
            }
            if (state == EnemyStates::AGRESSIVE && searchingTimer.getElapsedTime().asSeconds() >= SEARCHING_DURATION) {
                state = EnemyStates::PATROLLING;
            }
            return;
        }

        float knyazLeft = knyaz.getLeft();

        if (state == EnemyStates::AGRESSIVE && (knyazLeft >= LEFT_ACTIVE_EDGE || knyazLeft <= RIGHT_ACTIVE_EDGE)) {
            if (!seeKnyaz) {
                seeKnyaz = true;
            }
        } else if (
                state == EnemyStates::PATROLLING && (
                    !isPatrolingLeft && knyazLeft >= getRight() && knyazLeft <= RIGHT_ACTIVE_EDGE ||
                    isPatrolingLeft && knyazLeft <= getLeft()  && knyazLeft >= LEFT_ACTIVE_EDGE
                )
        ) {
            state = EnemyStates::AGRESSIVE;
            if (!seeKnyaz) {
                seeKnyaz = true;
            }
        } else if (knyazLeft <= LEFT_ACTIVE_EDGE || knyazLeft >= RIGHT_ACTIVE_EDGE) {
            if (seeKnyaz) {
                seeKnyaz = false;
                searchingTimer.restart();
            }
        }
    };

    void textureUpdate() override {
        return;
    }
};

void initDepends();
void initVariables();

void initGameMap();

extern vector<GameEntity> mapObjs;

#endif //KNYAZ_GAME_GLOBALS_H
