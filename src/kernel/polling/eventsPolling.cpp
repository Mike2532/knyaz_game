#include "./globals/globals.h"
#include "./ui/helpMenu/helpMenu.h"
#include "./ui/loadScreen/loadScreen.h"
#include "./ui/gameEnd/gameEnd.h"
#include "./knyaz/eventsHandler/eventsHandler.h"

void pollEvents() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        switch (curState) {
            case GameState::MAIN_MENU:
                mainMenuEventsHandler(event);
                break;
            case GameState::HELP_MENU:
                helpMenuEventsHandler(event);
                break;
            case GameState::LOAD_SCREEN_2:
                LoadScreenEventsHandler(event);
                break;
            case GameState::GAME_PROCESS:
                knyazEventsHandler(event);
                break;
            case GameState::GAME_END:
                GameEndEventsHandler(event);
                break;
        }
    }
}
