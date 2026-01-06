#include <SFML/Window.hpp>
#include "../utils/text.h"
#include "./mainMenuStruct.h"
#include "../../globals/globals.h"
#include "../../resources/BG/BG.h"

MainMenu mainMenu;

MainMenu getMainMenu() {
    const sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    const unsigned int SCREEN_WIDTH = desktopMode.width;
    const unsigned int SCREEN_HEIGHT = desktopMode.height;

    const int Y_OFFSET = 25;

    const auto getXPosition = [SCREEN_WIDTH] (sf::FloatRect textInfo) -> float {
        return SCREEN_WIDTH/2 - textInfo.width/2;
    };

    sf::Text startText = makeText("start");
    sf::Text settingsText = makeText("help");
    sf::Text exitText = makeText("exit");

    sf::FloatRect settingsTextInfo = settingsText.getLocalBounds();
    settingsText.setPosition(getXPosition(settingsTextInfo), SCREEN_HEIGHT/2 - settingsTextInfo.height/2);
    settingsTextInfo = settingsText.getGlobalBounds();

    sf::FloatRect startTextInfo = startText.getGlobalBounds();
    startText.setPosition(getXPosition(startTextInfo), settingsTextInfo.top - startTextInfo.height - Y_OFFSET);
    startTextInfo = startText.getGlobalBounds();

    sf::FloatRect exitTextInfo = exitText.getGlobalBounds();
    exitText.setPosition(getXPosition(exitTextInfo), settingsTextInfo.top + settingsTextInfo.height + Y_OFFSET);
    exitTextInfo = exitText.getGlobalBounds();

    return {
            startText,
            startTextInfo,
            settingsText,
            settingsTextInfo,
            exitText,
            exitTextInfo
    };
}

void mainMenuMouseClickHandler(const sf::Event& event) {
    const int eventX = event.mouseButton.x;
    const int eventY = event.mouseButton.y;

    auto checkButtonMatch = [eventX, eventY] (const sf::FloatRect& textInfo) -> bool {
        if (
                eventX >= textInfo.left &&
                eventX <= textInfo.left + textInfo.width &&
                eventY >= textInfo.top &&
                eventY <= textInfo.top + textInfo.height
                ) {
            return true;
        }
        return false;
    };

    if (checkButtonMatch(mainMenu.startTextInfo)) {
        globalTimer.restart();
        curState = GameState::LOAD_SCREEN_1;
        updateBGSprite();
    } else if (checkButtonMatch(mainMenu.settingsTextInfo)) {
        curState = GameState::HELP_MENU;
        updateBGSprite();
    } else if (checkButtonMatch(mainMenu.exitTextInfo)) {
        window.close();
    }
}

void mainMenuEventsHandler(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        mainMenuMouseClickHandler(event);
    }
}