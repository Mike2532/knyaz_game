////
//// Created by Миша Чулков on 22.11.2025.
////
//
//#include "string"
//#include "map"
//#include "./../config/config.h"
//#include "./../Models/GameState/GameState.h"
//#include "./../Models/MainMenu/MainMenu.h"
//
//
//using namespace std;
//
//using SettingsMenu = vector<sf::Text>;
//
//sf::RenderWindow getWindow() {
//    return {
//            sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}),
//            config["GAME_NAME"]
//    };
//}
//
//
//void initVariables() {
//    map<string, string> config = initConfig();
//    map<string, sf::Keyboard::Scancode> keymap = getKeymap();
//    sf::RenderWindow window = getWindow();
//    GameState curState = GameState::MAIN_MENU;
//    SettingsMenu settingsMenu = getSettingsMenu();
//    sf::Clock globalTimer;
//    MainMenu mainMenu;
//}