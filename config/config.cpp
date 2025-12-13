#include "map"
#include "string"

#include <SFML/Window.hpp>

using namespace std;

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
        {"GROUND_TEXTURE", "ground.jpg"},
        {"LAVA_TEXTURE", "lava.jpg"},
        {"SPIKES_TEXTURE", "spikesRight.png"},
        {"SPIKES_UP_TEXTURE", "spikesUp.png"},
        {"ENEMYS_ANIMATION_FOLDER", "./../media/animations/enemys/"},
        {"ENEMY_WALK_ANIMATION", "walk.png"},
        {"ENEMY_ATTACK_ANIMATION", "attack.png"},
        {"ENEMY_IDLE_ANIMATION", "idle.png"},
    };
}

map<string, sf::Keyboard::Scancode> getKeymap() {
    return {
        {"MOVE_LEFT_KEY", sf::Keyboard::Scancode::A},
        {"MOVE_RIGHT_KEY", sf::Keyboard::Scancode::D},
        {"JUMP_KEY", sf::Keyboard::Scancode::Space},
        {"RAGE_KEY", sf::Keyboard::Scancode::R},
        {"FOCUS_KEY", sf::Keyboard::Scancode::F},
        {"CLIMBING_KEY", sf::Keyboard::Scancode::E}
    };
}