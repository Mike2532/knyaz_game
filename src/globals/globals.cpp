#include "globals.h"
#include "../types.h"
#include "string"

sf::Texture MainMenuTexture;
sf::Texture HelpMenuTexture;
sf::Texture LoadScreenOneTexture;
sf::Texture LoadScreenTwoTexture;
sf::Texture GameProcessTexture;
sf::Texture GameEndTexture;

sf::Texture KnyazIdleTexture;
sf::Texture KnyazRunTexture;
sf::Texture KnyazJumpTexture;
sf::Texture KnyazFallingTexture;
sf::Texture KnyazEasyAttackTexture;
sf::Texture KnyazHeavyAttackTexture;


sf::Music GameMusic;
sf::Font myFont;
sf::Sprite BGSprite;

std::map<std::string, AnimationData> animationContainer;

Knyaz knyaz;
MainMenu mainMenu;
SettingsMenu settingsMenu;
sf::RenderWindow window;

//TODO в прод разкомментировать
//GameState curState = GameState::MAIN_MENU;
//TODO в прод закомментировать
GameState curState = GameState::GAME_PROCESS;



std::map<std::string, std::string> config;
std::map<std::string, sf::Keyboard::Scancode> keymap;
sf::Clock globalTimer;