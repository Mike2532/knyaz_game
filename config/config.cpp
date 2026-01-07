#include <SFML/Window.hpp>
#include "map"
#include "string"

using namespace std;

map<std::string, std::string> config;

map<string, string> initConfig() {
    return {
        {"MAIN_MENU_BG", "MMBG.png"},
        {"HELP_MENU_BG", "HBG.png"},
        {"LOAD_SCREEN_BG_FIRST", "loadScreen1.png"},
        {"LOAD_SCREEN_BG_SECOND", "loadScreen2.png"},
        {"GAME_PROCESS_BG", "gameProcess.png"},
        {"GAME_END_BG", "gameEnd.png"},
        {"FONT_PATH", "./../media/fonts/Wild-Rune.otf"},
        {"BG_TEXTURE_FOLDER", "./../media/backgrounds/"},
        {"MUSIC_FOLDER", "./../media/music/"},
        {"GAME_MUSIC_FILE", "gameMusic.ogg"},
        {"GAME_NAME", "Knyaz Vladimir Game"},
        {"MOVE_LEFT_KEY", "A"},
        {"MOVE_RIGHT_KEY", "D"},
        {"JUMP_KEY", "SPACE"},
        {"RAGE_KEY", "R"},
        {"FOCUS_KEY", "F"},
        {"CLIMBING_KEY", "E"},
        {"LIGHT_ATTACK_KEY", "LMB"},
        {"HEAVY_ATTACK_KEY", "RMB"},
        {"KNYAZ_ANIMATIOS_FOLDER", "./../media/animations/knyaz/"},
        {"KNYAZ_IDLE_ANIMATION", "idle.png"},
        {"KNYAZ_RUN_ANIMATION", "run.png"},
        {"KNYAZ_JUMP_ANIMATION", "jump.png"},
        {"KNYAZ_FALLING_ANIMATION", "falling.png"},
        {"KNYAZ_EASY_ATTACK_ANIMATION", "easyAttack.png"},
        {"KNYAZ_HEAVY_ATTACK_ANIMATION", "heavyAttack.png"},
        {"KNYAZ_DEATH_ANIMATION", "death.png"},
        {"KNYAZ_WALL_HANG_ANIMATION", "wallHang.png"},
        {"UI_TEXTURES_FOLDER", "../media/ui/"},
        {"HP_INDICATOR_TEXTURE", "HpIndicator.png"},
        {"WORLD_TEXTURES_FOLDER", "../media/objsTextures/"},
        {"BOTTLE_TEXTURE", "bottle.png"},
        {"GROUND_TEXTURE", "ground.jpg"},
        {"LAVA_TEXTURE", "lava.jpg"},
        {"SPIKES_TEXTURE", "spikesRight.png"},
        {"SPIKES_UP_TEXTURE", "spikesUp.png"},
        {"ENEMYS_ANIMATION_FOLDER", "./../media/animations/enemys/"},
        {"ENEMY_WALK_ANIMATION", "walk.png"},
        {"ENEMY_ATTACK_ANIMATION", "attack.png"},
        {"ENEMY_IDLE_ANIMATION", "idle.png"},
        {"TP_ENTIYES_FOLDER", "./../media/animations/tpEntitys/"},
        {"TP_ENTIYES_TEXTURE", "tpEntitys.png"},

        {"STRIKES_AIR_FOLDER", "media/music/fx/strikes/air/"},
        {"STRIKE_AIR_1", "ai1.wav"},
        {"STRIKE_AIR_2", "ai2.wav"},
        {"STRIKE_AIR_3", "ai3.wav"},
        {"STRIKE_AIR_4", "ai4.wav"},
        {"STRIKE_AIR_5", "ai5.wav"},
        {"STRIKE_AIR_6", "ai6.wav"},
        {"STRIKE_AIR_7", "ai7.wav"},
        {"STRIKE_AIR_8", "ai8.wav"},

        {"STRIKES_ARMOR_FOLDER", "media/music/fx/strikes/armor/"},
        {"STRIKE_ARMOR_1", "ar1.wav"},
        {"STRIKE_ARMOR_2", "ar2.wav"},
        {"STRIKE_ARMOR_3", "ar3.wav"},
        {"STRIKE_ARMOR_4", "ar4.wav"},

        {"STRIKES_FLASH_FOLDER", "media/music/fx/strikes/flash/"},
        {"STRIKE_FLASH_1", "f1.wav"},
        {"STRIKE_FLASH_2", "f2.wav"},
        {"STRIKE_FLASH_3", "f3.wav"},
        {"STRIKE_FLASH_4", "f4.wav"},
        {"STRIKE_FLASH_5", "f5.wav"},

        {"KNYAZ_RUN_FOLDER", "media/music/fx/run/"},
        {"KNYAZ_RUN_SOUND", "knyaz.wav"},

        {"KNYAZ_LANDING_FOLDER", "media/music/fx/landing/"},
        {"KNYAZ_LANDING_SOUND_1", "l1.wav"},
        {"KNYAZ_LANDING_SOUND_2", "l2.wav"},

        {"WIND_SOUND_FOLDER", "media/music/fx/wind/"},
        {"WIND_SOUND_1", "w1.wav"},
        {"WIND_SOUND_2", "w2.wav"},
        {"WIND_SOUND_3", "w3.wav"},

        {"BOTTLE_SOUND_FOLDER", "media/music/fx/bottle/"},
        {"BOTTLE_SOUND", "bottle.wav"},

        {"TP_SOUND_FOLDER", "media/music/fx/tp/"},
        {"TP_SOUND", "tp.wav"},

        {"RAGE_SOUND_FOLDER", "media/music/fx/rage/"},
        {"RAGE_SOUND", "rage.wav"},
    };
}

map<string, sf::Keyboard::Scancode> getKeymap() {
    return {
        {"MOVE_LEFT_KEY", sf::Keyboard::Scancode::A},
        {"MOVE_RIGHT_KEY", sf::Keyboard::Scancode::D},
        {"JUMP_KEY", sf::Keyboard::Scancode::Space},
        {"ALTER_JUMP_KEY", sf::Keyboard::Scancode::W},
        {"RAGE_KEY", sf::Keyboard::Scancode::R},
        {"FOCUS_KEY", sf::Keyboard::Scancode::F},
        {"CLIMBING_KEY", sf::Keyboard::Scancode::E}
    };
}