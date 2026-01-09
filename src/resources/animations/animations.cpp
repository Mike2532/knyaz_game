#include "../../globals/globals.h"
#include "../../../config/config.h"
#include "./boss/boss.h"

sf::Texture KnyazIdleTexture;
sf::Texture KnyazRunTexture;
sf::Texture KnyazJumpTexture;
sf::Texture KnyazFallingTexture;
sf::Texture KnyazEasyAttackTexture;
sf::Texture KnyazHeavyAttackTexture;
sf::Texture KnyazDeathTexture;
sf::Texture KnyazWallHangTexture;

sf::Texture EnemyWalkTexture;
sf::Texture EnemyAttackTexture;
sf::Texture EnemyIDLETexture;

sf::Texture tpTexture;

void initAnimationTextures() {
    KnyazIdleTexture.loadFromFile(config["KNYAZ_ANIMATIOS_FOLDER"] + config["KNYAZ_IDLE_ANIMATION"]);
    KnyazRunTexture.loadFromFile(config["KNYAZ_ANIMATIOS_FOLDER"] + config["KNYAZ_RUN_ANIMATION"]);
    KnyazJumpTexture.loadFromFile(config["KNYAZ_ANIMATIOS_FOLDER"] + config["KNYAZ_JUMP_ANIMATION"]);
    KnyazFallingTexture.loadFromFile(config["KNYAZ_ANIMATIOS_FOLDER"] + config["KNYAZ_FALLING_ANIMATION"]);
    KnyazEasyAttackTexture.loadFromFile(config["KNYAZ_ANIMATIOS_FOLDER"] + config["KNYAZ_EASY_ATTACK_ANIMATION"]);
    KnyazHeavyAttackTexture.loadFromFile(config["KNYAZ_ANIMATIOS_FOLDER"] + config["KNYAZ_HEAVY_ATTACK_ANIMATION"]);
    KnyazDeathTexture.loadFromFile(config["KNYAZ_ANIMATIOS_FOLDER"] + config["KNYAZ_DEATH_ANIMATION"]);
    KnyazWallHangTexture.loadFromFile(config["KNYAZ_ANIMATIOS_FOLDER"] + config["KNYAZ_WALL_HANG_ANIMATION"]);
    EnemyWalkTexture.loadFromFile(config["ENEMYS_ANIMATION_FOLDER"] + config["ENEMY_WALK_ANIMATION"]);
    EnemyAttackTexture.loadFromFile(config["ENEMYS_ANIMATION_FOLDER"] + config["ENEMY_ATTACK_ANIMATION"]);
    EnemyIDLETexture.loadFromFile(config["ENEMYS_ANIMATION_FOLDER"] + config["ENEMY_IDLE_ANIMATION"]);
    tpTexture.loadFromFile(config["TP_ENTIYES_FOLDER"] + config["TP_ENTIYES_TEXTURE"]);
}

void initAnimations() {
    animationContainer["idle"] = {
            KnyazIdleTexture,
            10,
            AnimationTypes::IDLE
    };

    animationContainer["run"] = {
            KnyazRunTexture,
            10,
            AnimationTypes::RUN
    };

    animationContainer["jump"] = {
            KnyazJumpTexture,
            3,
            AnimationTypes::JUMP
    };

    animationContainer["falling"] = {
            KnyazFallingTexture,
            3,
            AnimationTypes::FALL
    };

    animationContainer["easyAttack"] = {
            KnyazEasyAttackTexture,
            4,
            AnimationTypes::ATTACK
    };

    animationContainer["heavyAttack"] = {
            KnyazHeavyAttackTexture,
            6,
            AnimationTypes::ATTACK
    };

    animationContainer["death"] = {
            KnyazDeathTexture,
            10,
            AnimationTypes::DEATH
    };

    animationContainer["wallHang"] = {
            KnyazWallHangTexture,
            1,
            AnimationTypes::CLIMB
    };

    animationContainer["enemyWalk"] = {
            EnemyWalkTexture,
            8,
            AnimationTypes::RUN
    };

    animationContainer["enemyAttack"] = {
            EnemyAttackTexture,
            6,
            AnimationTypes::ATTACK
    };

    animationContainer["enemyIDLE"] = {
            EnemyIDLETexture,
            6,
            AnimationTypes::IDLE
    };

    animationContainer["tpEntityes"] = {
            tpTexture,
            6,
            AnimationTypes::IDLE
    };

    animationContainer["bossAttack0"] = {
            *bossTextures[bossTexturesKeys::attack0],
            6,
            AnimationTypes::ATTACK
    };

    animationContainer["bossAttack1"] = {
            *bossTextures[bossTexturesKeys::attack1],
            6,
            AnimationTypes::ATTACK
    };

    animationContainer["bossDeath"] = {
            *bossTextures[bossTexturesKeys::death],
            6,
            AnimationTypes::ATTACK
    };

    animationContainer["bossIDLE"] = {
            *bossTextures[bossTexturesKeys::idle],
            6,
            AnimationTypes::IDLE
    };

    animationContainer["bossWalk"] = {
            *bossTextures[bossTexturesKeys::walk],
            8,
            AnimationTypes::RUN
    };
}
