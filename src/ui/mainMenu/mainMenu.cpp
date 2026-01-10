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

    const auto getXPosition = [SCREEN_WIDTH](sf::FloatRect textInfo) -> float {
        return SCREEN_WIDTH / 2.f - textInfo.width / 2.f;
    };

    sf::Text startText = makeText("start");
    sf::Text exitText  = makeText("exit");

    sf::FloatRect startTextInfo = startText.getLocalBounds();
    startText.setPosition(
            getXPosition(startTextInfo),
            SCREEN_HEIGHT / 2.f - startTextInfo.height - Y_OFFSET / 2.f
    );
    startTextInfo = startText.getGlobalBounds();

    sf::FloatRect exitTextInfo = exitText.getLocalBounds();
    exitText.setPosition(
            getXPosition(exitTextInfo),
            SCREEN_HEIGHT / 2.f + Y_OFFSET / 2.f
    );
    exitTextInfo = exitText.getGlobalBounds();

    return {
            startText,
            startTextInfo,
            exitText,
            exitTextInfo
    };
}

void mainMenuMouseClickHandler(const sf::Event& event) {
    const int eventX = event.mouseButton.x;
    const int eventY = event.mouseButton.y;

    auto checkButtonMatch = [eventX, eventY](const sf::FloatRect& textInfo) -> bool {
        return
                eventX >= textInfo.left &&
                eventX <= textInfo.left + textInfo.width &&
                eventY >= textInfo.top &&
                eventY <= textInfo.top + textInfo.height;
    };

    if (checkButtonMatch(mainMenu.startTextInfo)) {
        globalTimer.restart();
        curState = GameState::LOAD_SCREEN_1;
        updateBGSprite();
    }
    else if (checkButtonMatch(mainMenu.exitTextInfo)) {
        window.close();
    }
}


void mainMenuEventsHandler(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        mainMenuMouseClickHandler(event);
    }
}