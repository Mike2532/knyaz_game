#include "./globals/globals.h"
#include "./BG/DrawerBG.h"
#include "./Menu/DrawerMenu.h"
#include "./Game/DrawerGame.h"

bool isMenuState() {
    return curState == GameState::MAIN_MENU || curState == GameState::HELP_MENU;
}

bool isGameState() {
    return curState == GameState::GAME_PROCESS;
}

void redrawFrame(const std::vector<sf::Text>& textToPrint) {
    window.clear();

    window.setView(UIView);
    drawBG();

    if (isMenuState()) {
        drawMenu(textToPrint);
    } else if (isGameState()) {
        drawGame();
    }

    window.display();
}