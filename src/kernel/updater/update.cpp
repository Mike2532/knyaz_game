#include "./globals/globals.h"
#include "./game/UpdateGame.h"
#include "./loadScreen/UpdaterLoadScreen.h"
#include "./mainMenu/UpdaterMainMenu.h"

using namespace std;

void update(std::vector<sf::Text>& textToPrint) {
    switch (curState) {
        case (GameState::MAIN_MENU):
            updateMainMenu(textToPrint);
            break;
        case (GameState::GAME_PROCESS):
            updateGame();
            break;
        case (GameState::LOAD_SCREEN_1):
            updateLoadScreen();
            break;
    }
}