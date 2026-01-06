#ifndef KNYAZ_GAME_GLOBALS_H
#define KNYAZ_GAME_GLOBALS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <vector>
#include "iostream"
#include "../types.h"
#include "../ui/mainMenu/mainMenu.h"

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

extern sf::Texture HpIndicatorTexture;

extern sf::Texture EnemyWalkTexture;
extern sf::Texture EnemyAttackTexture;
extern sf::Texture EnemyIDLETexture;

extern sf::Texture GroundTexture;
extern sf::Texture LavaTexture;
extern sf::Texture SpikesTexture;
extern sf::Texture SpikesUpTexture;

extern sf::Texture BottleTexture;

extern sf::Music GameMusic;
extern sf::Font myFont;
extern sf::Sprite BGSprite;
extern sf::Sprite HpIndicatorSprite;

extern bool lastTeleported;
extern sf::RectangleShape antiGravityField;

struct UI {
    sf::RectangleShape focusOutline;
    sf::RectangleShape focusFill;

    sf::RectangleShape rageOutline;
    sf::RectangleShape rageFill;
};

extern UI ui;

struct Portal {
    sf::Vector2f inCoords;
    sf::RectangleShape inBody;

    sf::Vector2f outCoords;
    sf::RectangleShape outBody;
};

struct AnimationData {
    sf::Texture animationTexture;
    int animationFrames;
    AnimationTypes animationType;
};

extern std::map<std::string, AnimationData> animationContainer;

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

    void animationProcess() {
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

    void changeAnimation(const AnimationData& newAnimation) {
        if (!isAlive) return;
        animationData = newAnimation;
        animationFrameNumber = 0;
        animationTimer.restart();
        textureUpdate();
    }
};

struct Knyaz : AnimatedObj {
    const int MAX_HP = 3000;
    const int MAX_FOCUS_COUNTER = 6;
    const int MAX_RAGE_COUNTER = 3;

    int lastHeatedEnemy;
    vector<string> actionsHistory;

    bool isMovingLeft = false;
    bool isMovingRight = false;
    bool isJump = false;
    bool isDoubleJump = false;
    bool isClimbing = false;

    bool isAttackFinished = false;
    bool isFlyingUp = false;

    int hp = MAX_HP;
    int lightAttackPower = 400;
    int heavyAttackPower = 700;
    int rageAttackPower = 2200;
    int takenDamage = 0;

    int rageCounter = 0;
    int focusCounter = 0;

    sf::Clock attackTimer;
    sf::Clock damageTimer;
    sf::Clock climbingTimer;

    void textureUpdate() override {
        constexpr int STRIP_FRAME_OFFSET = 120;
        constexpr int NORMAL_BASE_X = 27 + 17;
        constexpr int ATTACK_BASE_X = 40;

        constexpr int NORMAL_W = 43;
        constexpr int NORMAL_H = 40;
        constexpr int ATTACK_W = 65;
        constexpr int ATTACK_H = 45;

        constexpr int NORMAL_TOP = 40;
        constexpr int ATTACK_TOP = 35;

        objSprite.setTexture(animationData.animationTexture);
        if (animationData.animationType == AnimationTypes::ATTACK) {
            objSprite.setTextureRect(sf::IntRect(
                    STRIP_FRAME_OFFSET * animationFrameNumber + ATTACK_BASE_X - 15.f,
                    ATTACK_TOP,
                    ATTACK_W + 15.f,
                    ATTACK_H
            ));

            if (animationFrameNumber == animationData.animationFrames - 1) {
                if (isAlive) changeAnimation(animationContainer["idle"]);
                objSprite.setTextureRect(sf::IntRect(
                        STRIP_FRAME_OFFSET * animationFrameNumber + NORMAL_BASE_X - 15.f,
                        NORMAL_TOP,
                        NORMAL_W  + 15.f,
                        NORMAL_H
                ));
            }
        } else {
            objSprite.setTextureRect(sf::IntRect(
                    STRIP_FRAME_OFFSET * animationFrameNumber + NORMAL_BASE_X  - 15.f,
                    NORMAL_TOP,
                    NORMAL_W + 15.f,
                    NORMAL_H
            ));
        }
        isAttackFinished = true;
        float scaleX = 2.f;
        float scaleY = 2.f;

        if (isLeftOrented) {
            scaleX *= -1;
            if (!isSpriteLeftOrented) isSpriteLeftOrented = true;
        } else if (isSpriteLeftOrented) {
            isSpriteLeftOrented = false;
        }

        objSprite.setScale(scaleX, scaleY);
    }

    void spritePositionUpdate() {
        sf::Vector2f pos = body.getPosition();
        pos.x -= 30;
        pos.y -= 5;
        if (animationData.animationType == AnimationTypes::ATTACK) {
            pos.y -= 10;
        }

        if (isSpriteLeftOrented) {
            pos.x += 105;
        }
        objSprite.setPosition(pos);
    }

    void takeDamage() {
        constexpr float damageMilliseconds = 400;
        if (takenDamage != 0 && damageTimer.getElapsedTime().asMilliseconds() >= damageMilliseconds) {
            rageCounter = min(rageCounter + 1, MAX_RAGE_COUNTER);
            objSprite.setColor(sf::Color::White);
            takenDamage = 0;
        }
    }
};

extern Knyaz knyaz;
extern sf::RenderWindow window;
extern GameState curState;
extern std::map<std::string, sf::Keyboard::Scancode> keymap;
extern sf::Clock globalTimer;

struct Enemy : AnimatedObj {
    int id;
    int MAX_HP = 2000;
    float STUNNED_TIME = 3.f;

    float LEFT_PATROLING_EDGE;
    float RIGHT_PATROLING_EDGE;
    float LEFT_ACTIVE_EDGE;
    float RIGHT_ACTIVE_EDGE;

    bool isNearLeftKnyaz = false;
    bool isNearRightKnyaz = false;
    bool seeKnyaz = false;
    bool isPatrolingLeft = true;
    bool isAttacking = false;

    sf::Clock stunnedTimer;

    int hp = MAX_HP;
    int attackPower = 650;
    int takenDamage = 0;

    sf::Clock searchingTimer;
    sf::Clock attackTimer;
    EnemyStates state = EnemyStates::PATROLLING;

    void move(const float& elapsedTime) {
        if (isStunned) {
            return;
        }
        if ((isNearLeftKnyaz || isNearRightKnyaz) && animationData.animationType != AnimationTypes::IDLE && animationData.animationType != AnimationTypes::ATTACK) {
            changeAnimation(animationContainer["enemyIDLE"]);
            attackTimer.restart();
        } else if (!(isNearLeftKnyaz || isNearRightKnyaz) && animationData.animationType == AnimationTypes::ATTACK) {
            changeAnimation(animationContainer["enemyIDLE"]);
        }

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
        if (isStunned) {
            return;
        }
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
                changeAnimation(animationContainer["enemyWalk"]);
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

    bool isAttackingNow(int x) {
        constexpr float k = 0.08;
        constexpr int x0 = 650;
        double y = (1.0 / (1.0 + exp(-k * (x - x0)))) * 10000.0;
        int r2 = rand() % 10000;
        return r2 <= y;
    }

    void tryToAttack() {
        if (isStunned) {
            return;
        }
        if (!knyaz.isAlive) return;
        bool isAttacking = isAttackingNow(attackTimer.getElapsedTime().asMilliseconds());

        if ((isNearLeftKnyaz || isNearRightKnyaz) && animationData.animationType != AnimationTypes::ATTACK && isAttacking) {
            changeAnimation(animationContainer["enemyAttack"]);
        }
    }

    void textureUpdate() override {
        constexpr int FRAME_WIDTH = 100;
        constexpr int X_OFFSET = 44;
        constexpr int Y_OFFSET = 41;
        constexpr int ANIMATION_WIDTH = 22;
        constexpr int ANIMATION_HEIGHT = 16;

        objSprite.setTexture(animationData.animationTexture);

        objSprite.setTextureRect(sf::IntRect(
                FRAME_WIDTH * animationFrameNumber + X_OFFSET - 10,
                Y_OFFSET - 10,
                ANIMATION_WIDTH + 20,
                ANIMATION_HEIGHT + 15
        ));

        float SCALE_X = 4.f;
        float SCALE_Y = 4.f;

        if (isPatrolingLeft) {
            isSpriteLeftOrented = true;
            SCALE_X *= -1;
        } else if (isSpriteLeftOrented) {
            isSpriteLeftOrented = false;
        }

        objSprite.setScale(SCALE_X, SCALE_Y);

        if (animationData.animationType == AnimationTypes::ATTACK) {
            if (animationFrameNumber == animationData.animationFrames - 1) {
                attackTimer.restart();
                changeAnimation(animationContainer["enemyIDLE"]);
            } else if (animationFrameNumber == animationData.animationFrames - 3) {
                knyaz.hp -= attackPower;
                knyaz.hp = max(knyaz.hp, 0);
                if (knyaz.hp == 0) {
                    knyaz.changeAnimation(animationContainer["death"]);
                    knyaz.isAlive = false;
                }
                knyaz.takenDamage += attackPower;
                knyaz.objSprite.setColor(sf::Color::Red);
                knyaz.damageTimer.restart();
            }

        }

        if (animationFrameNumber == animationData.animationFrames - 1 && animationData.animationType == AnimationTypes::ATTACK) {
            attackTimer.restart();
            changeAnimation(animationContainer["enemyIDLE"]);
        }
    }

    void spritePositionUpdate() {
        sf::Vector2f pos = body.getPosition();
        pos.x -= 40;
        pos.y -= 40;
        if (isSpriteLeftOrented) {
            pos.x += 130;
        }
        objSprite.setPosition(pos);
    }

    void stunProcess() {
        if (!isStunned) {
            return;
        }
        if (stunnedTimer.getElapsedTime().asSeconds() >= STUNNED_TIME) {
            isStunned = false;
        }
    }
};

void initDepends();
void initVariables();

void initGameMap();
void initEnemys();
void initMapPortals();
void initAntiGravityField();

extern vector<GameEntity> mapObjs;
extern vector<Enemy> mapEnemys;
extern vector<Portal> mapPortals;

extern void enemysTakenDamage();
extern void removeBottleByCoords(sf::Vector2f coords);
#endif //KNYAZ_GAME_GLOBALS_H
