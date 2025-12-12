#ifndef KNYAZ_GAME_GLOBALS_H
#define KNYAZ_GAME_GLOBALS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <vector>
#include "iostream"
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

extern sf::Texture EnemyWalkTexture;

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
    bool isAttackFinished = false;

    int hp = 2500;
    int lightAttackPower = 400;
    int heavyAttackPower = 700;

    sf::Clock attackTimer;
    sf::Clock climbingTimer;

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
                isAttackFinished = true;
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
            isAttackFinished = true;
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

struct Enemy : AnimatedObj {
    float LEFT_PATROLING_EDGE;
    float RIGHT_PATROLING_EDGE;
    float LEFT_ACTIVE_EDGE;
    float RIGHT_ACTIVE_EDGE;

    bool isNearLeftKnyaz = false;
    bool isNearRightKnyaz = false;
    bool seeKnyaz = false;
    bool isPatrolingLeft = true;

    int hp = 1000;
    int attackPower = 250;
    int takenDamage = 0;

    sf::Clock searchingTimer;
    EnemyStates state = EnemyStates::PATROLLING;

    void move(const float& elapsedTime) {
        float PATROL_SPEED = 125.f;
        float AGRESSIVE_SPEED = 250.f;
        sf::Vector2f enemyPos = body.getPosition();

        if (state == EnemyStates::PATROLLING) {
            if (isPatrolingLeft) {
                if (getLeft() > LEFT_PATROLING_EDGE) {
                    enemyPos.x -= PATROL_SPEED * elapsedTime;
                    body.setPosition(enemyPos);
                } else {
                    isPatrolingLeft = false;
                }
            } else {
                if (getRight() < RIGHT_PATROLING_EDGE) {
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

            if (isKnyazLeft && !needToLeftRun && !isNearLeftKnyaz) {
                isNearLeftKnyaz = true;
                isNearRightKnyaz = false;
            }

            if (isKnyazRight && !needToRightRun && !isNearRightKnyaz) {
                isNearRightKnyaz = true;
                isNearLeftKnyaz = false;
            }

            if (isKnyazLeft && needToLeftRun) {
                enemyPos.x -= AGRESSIVE_SPEED * elapsedTime;
                enemyPos.x = max(enemyPos.x, LEFT_ACTIVE_EDGE);
                isPatrolingLeft = true;
                body.setPosition(enemyPos);
                if (isNearLeftKnyaz) {
                    isNearLeftKnyaz = false;
                }
            } else if (isKnyazRight && needToRightRun) {
                enemyPos.x += AGRESSIVE_SPEED * elapsedTime;
                enemyPos.x = min(enemyPos.x, RIGHT_ACTIVE_EDGE - body.getSize().x);
                isPatrolingLeft = false;
                body.setPosition(enemyPos);
                if (isNearRightKnyaz) {
                    isNearRightKnyaz = false;
                }
            }
        }
    }

    void checkKnyazVision() {
        constexpr float SEARCHING_DURATION = 2.f;
        bool isKnyazUpperOrLower = knyaz.getTop() >= getBot() || knyaz.getBot() <= getTop();

        if (isKnyazUpperOrLower) {
            if (seeKnyaz) {
                seeKnyaz = false;
                if (isNearLeftKnyaz) {
                    isNearLeftKnyaz = false;
                }
                if (isNearRightKnyaz) {
                    isNearRightKnyaz = false;
                }
                searchingTimer.restart();
            }
            if (state == EnemyStates::AGRESSIVE && searchingTimer.getElapsedTime().asSeconds() >= SEARCHING_DURATION) {
                state = EnemyStates::PATROLLING;
            }
            return;
        }

        float knyazLeft = knyaz.getLeft();
        float knyazRight = knyaz.getRight();

        if (state == EnemyStates::AGRESSIVE && (knyazRight >= LEFT_ACTIVE_EDGE || knyazLeft <= RIGHT_ACTIVE_EDGE)) {
            if (!seeKnyaz) {
                seeKnyaz = true;
            }
        } else if (
                state == EnemyStates::PATROLLING && (
                    !isPatrolingLeft && knyazLeft >= getRight() && knyazLeft <= RIGHT_ACTIVE_EDGE ||
                    isPatrolingLeft && knyazLeft <= getLeft()  && knyazRight >= LEFT_ACTIVE_EDGE
                )
        ) {
            state = EnemyStates::AGRESSIVE;
            if (!seeKnyaz) {
                seeKnyaz = true;
            }
        } else if (knyazRight <= LEFT_ACTIVE_EDGE || knyazLeft >= RIGHT_ACTIVE_EDGE) {
            if (seeKnyaz) {
                seeKnyaz = false;
                if (isNearLeftKnyaz) {
                    isNearLeftKnyaz = false;
                }
                if (isNearRightKnyaz) {
                    isNearRightKnyaz = false;
                }
                searchingTimer.restart();
            }
        }
    };

    void textureUpdate() override {
        constexpr float ENEMY_SIDE_SIZE = 80.f;

        constexpr int FRAME_WIDTH = 100;
        constexpr int X_OFFSET = 44;
        constexpr int Y_OFFSET = 41;
        constexpr int ANIMATION_WIDTH = 22;
        constexpr int ANIMATION_HEIGHT = 16;

        body.setTexture(&animationData.animationTexture);

        if (isPatrolingLeft) {
            body.setTextureRect(sf::IntRect(
                    FRAME_WIDTH * animationFrameNumber + X_OFFSET + ANIMATION_WIDTH,
                    Y_OFFSET,
                    -ANIMATION_WIDTH,
                    ANIMATION_HEIGHT
            ));
        } else {
            body.setTextureRect(sf::IntRect(
                    FRAME_WIDTH * animationFrameNumber + X_OFFSET,
                    Y_OFFSET,
                    ANIMATION_WIDTH,
                    ANIMATION_HEIGHT
            ));
        }

        body.setSize(sf::Vector2f(ENEMY_SIDE_SIZE, ENEMY_SIDE_SIZE));
    }
};

void initDepends();
void initVariables();

void initGameMap();
void initEnemys();

extern vector<GameEntity> mapObjs;
extern vector<Enemy> mapEnemys;

extern void enemysTakenDamage();
#endif //KNYAZ_GAME_GLOBALS_H
