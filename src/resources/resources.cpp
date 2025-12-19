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
    BottleTexture.loadFromFile(config["WORLD_TEXTURES_FOLDER"] + config["BOTTLE_TEXTURE"]);
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

void initUI() {
    constexpr float BAR_LENGTH = 10.f;
    constexpr float BAR_HEIGHT = 70.f;
    constexpr float X_OFFSET = 1400.f;
    constexpr float Y_OFFSET = 700.f;
    constexpr float SPACE_BETWEEN = 20.f;

    ui.focusOutline.setPosition({X_OFFSET, Y_OFFSET});
    ui.focusOutline.setSize({BAR_LENGTH, BAR_HEIGHT});
    ui.focusOutline.setOutlineThickness(3.f);
    ui.focusOutline.setOutlineColor(sf::Color::Black);

    ui.focusFill.setPosition({X_OFFSET, Y_OFFSET + BAR_HEIGHT});
    ui.focusFill.setSize({BAR_LENGTH, 0});
    ui.focusFill.setFillColor(sf::Color::Blue);

    ui.rageOutline.setPosition({X_OFFSET + SPACE_BETWEEN, Y_OFFSET});
    ui.rageOutline.setSize({BAR_LENGTH, BAR_HEIGHT});
    ui.rageOutline.setOutlineThickness(3.f);
    ui.rageOutline.setOutlineColor(sf::Color::Black);

    ui.rageFill.setPosition({X_OFFSET + SPACE_BETWEEN, Y_OFFSET + BAR_HEIGHT});
    ui.rageFill.setSize({BAR_LENGTH, 0});
    ui.rageFill.setFillColor(sf::Color::Red);
}

void updateUI() {
    constexpr float BAR_LENGTH = 10.f;
    constexpr float BAR_HEIGHT = 70.f;

    ui.focusFill.setSize({BAR_LENGTH, -BAR_HEIGHT * knyaz.focusCounter/knyaz.MAX_FOCUS_COUNTER});
    ui.rageFill.setSize({BAR_LENGTH, -BAR_HEIGHT * knyaz.rageCounter/knyaz.MAX_RAGE_COUNTER});
}