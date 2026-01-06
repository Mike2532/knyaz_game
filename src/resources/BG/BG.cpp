#include "../../../config/config.h"
#include "../../globals/globals.h"

sf::Texture MainMenuTexture;
sf::Texture HelpMenuTexture;
sf::Texture LoadScreenOneTexture;
sf::Texture LoadScreenTwoTexture;
sf::Texture GameProcessTexture;
sf::Texture GameEndTexture;

void initBGTexture() {
    MainMenuTexture.loadFromFile(config["BG_TEXTURE_FOLDER"] + config["MAIN_MENU_BG"]);
    HelpMenuTexture.loadFromFile(config["BG_TEXTURE_FOLDER"] + config["HELP_MENU_BG"]);
    LoadScreenOneTexture.loadFromFile(config["BG_TEXTURE_FOLDER"] + config["LOAD_SCREEN_BG_FIRST"]);
    LoadScreenTwoTexture.loadFromFile(config["BG_TEXTURE_FOLDER"] + config["LOAD_SCREEN_BG_SECOND"]);
    GameProcessTexture.loadFromFile(config["BG_TEXTURE_FOLDER"] + config["GAME_PROCESS_BG"]);
    GameEndTexture.loadFromFile(config["BG_TEXTURE_FOLDER"] + config["GAME_END_BG"]);
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