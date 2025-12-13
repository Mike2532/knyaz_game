#include "resources.h"
#include "../globals/globals.h"
#include "../types.h"
#include <iostream>
#include "map"
#include "string"

using namespace std;

void initFont() {
    if (!myFont.loadFromFile(config["FONT_PATH"])) {
        std::cerr << "Failed to load font: " << config["FONT_PATH"] << "\n";
    }
}

void initGameMusic() {
    if (!GameMusic.openFromFile(config["MUSIC_FOLDER"] + config["GAME_MUSIC_FILE"])) {
        std::cerr << "Failed to open music file\n";
    } else {
        GameMusic.setVolume(5);
        GameMusic.setLoop(true);
    }
}

void initBGTexture() {
    MainMenuTexture.loadFromFile(config["BG_TEXTURE_FOLDER"] + config["MAIN_MENU_BG"]);
    HelpMenuTexture.loadFromFile(config["BG_TEXTURE_FOLDER"] + config["HELP_MENU_BG"]);
    LoadScreenOneTexture.loadFromFile(config["BG_TEXTURE_FOLDER"] + config["LOAD_SCREEN_BG_FIRST"]);
    LoadScreenTwoTexture.loadFromFile(config["BG_TEXTURE_FOLDER"] + config["LOAD_SCREEN_BG_SECOND"]);
    GameProcessTexture.loadFromFile(config["BG_TEXTURE_FOLDER"] + config["GAME_PROCESS_BG"]);
    GameEndTexture.loadFromFile(config["BG_TEXTURE_FOLDER"] + config["GAME_END_BG"]);
}

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
}

void initObjsTextures() {
    GroundTexture.loadFromFile(config["WORLD_TEXTURES_FOLDER"] + config["GROUND_TEXTURE"]);
    LavaTexture.loadFromFile(config["WORLD_TEXTURES_FOLDER"] + config["LAVA_TEXTURE"]);
    SpikesTexture.loadFromFile(config["WORLD_TEXTURES_FOLDER"] + config["SPIKES_TEXTURE"]);
    SpikesUpTexture.loadFromFile(config["WORLD_TEXTURES_FOLDER"] + config["SPIKES_UP_TEXTURE"]);
}

void initUITextures() {
    HpIndicatorTexture.loadFromFile(config["UI_TEXTURES_FOLDER"] + config["HP_INDICATOR_TEXTURE"]);
}

void playGameMusic() {
    GameMusic.play();
}

void updateBGSprite() {
    switch (curState) {
        case GameState::MAIN_MENU:    BGSprite = sf::Sprite(MainMenuTexture); break;
        case GameState::HELP_MENU:    BGSprite = sf::Sprite(HelpMenuTexture); break;
        case GameState::LOAD_SCREEN_1:BGSprite = sf::Sprite(LoadScreenOneTexture); break;
        case GameState::LOAD_SCREEN_2:BGSprite = sf::Sprite(LoadScreenTwoTexture); break;
        case GameState::GAME_PROCESS: BGSprite = sf::Sprite(GameProcessTexture); break;
        case GameState::GAME_END:     BGSprite = sf::Sprite(GameEndTexture); break;
    }
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
}