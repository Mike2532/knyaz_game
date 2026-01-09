#include "../knyaz/knyaz.h"
#include "./Enemy.h"
#include "../resources/sounds/fx/fight/fight.h"

void Enemy::move(const float &elapsedTime) {
    if (isStunned) {
        return;
    }
    if ((isNearLeftKnyaz || isNearRightKnyaz) && animationData.animationType != AnimationTypes::IDLE && animationData.animationType != AnimationTypes::ATTACK) {
        if (isBoss) {
            changeAnimation(animationContainer["bossIDLE"]);
        } else {
            changeAnimation(animationContainer["enemyIDLE"]);
        }
        attackTimer.restart();
    } else if (!(isNearLeftKnyaz || isNearRightKnyaz) && animationData.animationType == AnimationTypes::ATTACK) {
        if (isBoss) {
            changeAnimation(animationContainer["bossIDLE"]);
        } else {
            changeAnimation(animationContainer["enemyIDLE"]);
        }
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
            if (animationData.animationType == AnimationTypes::IDLE && seeKnyaz) {
                if (isBoss) {
                    changeAnimation(animationContainer["bossWalk"]);
                } else {
                    changeAnimation(animationContainer["enemyWalk"]);
                }
            }

            enemyPos.x -= AGRESSIVE_SPEED * elapsedTime;
            enemyPos.x = max(enemyPos.x, LEFT_ACTIVE_EDGE);
            isPatrolingLeft = true;
            body.setPosition(enemyPos);
            if (isNearLeftKnyaz) {
                isNearLeftKnyaz = false;
            }
        } else if (isKnyazRight && needToRightRun && !needToReverse) {
            if (animationData.animationType == AnimationTypes::IDLE && seeKnyaz) {
                if (isBoss) {
                    changeAnimation(animationContainer["bossWalk"]);
                } else {
                    changeAnimation(animationContainer["enemyWalk"]);
                }
            }

            enemyPos.x += AGRESSIVE_SPEED * elapsedTime;
            enemyPos.x = min(enemyPos.x, RIGHT_ACTIVE_EDGE - body.getSize().x);
            isPatrolingLeft = false;
            body.setPosition(enemyPos);
            if (isNearRightKnyaz) {
                isNearRightKnyaz = false;
            }
        }
    } else if (state == EnemyStates::AGRESSIVE && !seeKnyaz && animationData.animationType == AnimationTypes::RUN) {
        if (isBoss) {
            changeAnimation(animationContainer["bossIDLE"]);
        } else {
            changeAnimation(animationContainer["enemyIDLE"]);
        }
    }
}

void Enemy::checkKnyazVision() {
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
            if (isBoss) {
                changeAnimation(animationContainer["bossWalk"]);
            } else {
                changeAnimation(animationContainer["enemyWalk"]);
            }
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
}

bool Enemy::isAttackingNow(int x) {
    constexpr float k = 0.08;
    constexpr int x0 = 650;
    double y = (1.0 / (1.0 + exp(-k * (x - x0)))) * 10000.0;
    int r2 = rand() % 10000;
    return r2 <= y;
}

void Enemy::tryToAttack() {
    if (isStunned) {
        return;
    }
    if (!knyaz.isAlive) return;
    bool isAttacking = isAttackingNow(attackTimer.getElapsedTime().asMilliseconds());

    if ((isNearLeftKnyaz || isNearRightKnyaz) && animationData.animationType != AnimationTypes::ATTACK && isAttacking) {
        if (isBoss) {
            changeAnimation(animationContainer["bossAttack0"]);
        } else {
            changeAnimation(animationContainer["enemyAttack"]);
        }
        playRandomAirSound();
    }
}

void Enemy::textureUpdate() {
    objSprite.setTexture(animationData.animationTexture);

    objSprite.setTextureRect(sf::IntRect(
            FRAME_WIDTH * animationFrameNumber + X_OFFSET,
            Y_OFFSET,
            ANIMATION_WIDTH,
            ANIMATION_HEIGHT
    ));

    float scaleX = ANIMATION_TEXTURE_SCALE_X;
    float scaleY = ANIMATION_TEXTURE_SCALE_Y;

    if (isPatrolingLeft) {
        isSpriteLeftOrented = true;
        scaleX = -abs(scaleX);
    } else {
        isSpriteLeftOrented = false;
        scaleX = abs(scaleX);
    }

    objSprite.setScale(scaleX, scaleY);

    if (animationData.animationType == AnimationTypes::ATTACK) {
        if (animationFrameNumber == animationData.animationFrames - 1) {
            attackTimer.restart();
            if (isBoss) {
                changeAnimation(animationContainer["bossIDLE"]);
            } else {
                changeAnimation(animationContainer["enemyIDLE"]);
            }
        } else if (animationFrameNumber == animationData.animationFrames - 3) {
            playRandomArmorSound();
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
        if (isBoss) {
            changeAnimation(animationContainer["bossIDLE"]);
        } else {
            changeAnimation(animationContainer["enemyIDLE"]);
        }
    }
}

void Enemy::spritePositionUpdate() {
    sf::Vector2f pos = body.getPosition();
    pos.x -= SPRITE_POS_X_OFFSET;
    pos.y -= SPRITE_POS_Y_OFFSET;

    if (!isBoss && isSpriteLeftOrented) {
        pos.x += SPRITE_POS_ADDITIONAL_OFFSET;
    } else if (isBoss && !isSpriteLeftOrented) {
        pos.x -= SPRITE_POS_ADDITIONAL_OFFSET;
    }

    objSprite.setPosition(pos);
}

void Enemy::stunProcess() {
    if (!isStunned) {
        return;
    }
    if (stunnedTimer.getElapsedTime().asSeconds() >= STUNNED_TIME) {
        isStunned = false;
    }
}

void Enemy::easyComboReversal() {
    if (needToReverse && reverseTimer.getElapsedTime().asMilliseconds() >= 700) {
        isPatrolingLeft = !isPatrolingLeft;
        needToReverse = false;
    }
}