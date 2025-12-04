#include "ui.h"
#include "../globals/globals.h"
#include "../resources/resources.h"
#include <iostream>

using namespace std;

sf::Text getText(const std::string& textContent) {
    const int CHARACTER_SIZE = 65;
    const float OUTLINE_THICKNESS = 1.5f;
    const sf::Color TEXT_COLOR = {0xFB, 0x2E, 0x00};
    const sf::Vector2f BASE_POSITION = {0, 0};

    sf::Text myTxt;
    myTxt.setPosition(BASE_POSITION);
    myTxt.setFont(myFont);
    myTxt.setFillColor(TEXT_COLOR);
    myTxt.setString(textContent);
    myTxt.setOutlineThickness(OUTLINE_THICKNESS);
    myTxt.setOutlineColor(sf::Color::Black);
    myTxt.setCharacterSize(CHARACTER_SIZE);
    return myTxt;
}

MainMenu getMainMenu() {
    const sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    const unsigned int SCREEN_WIDTH = desktopMode.width;
    const unsigned int SCREEN_HEIGHT = desktopMode.height;

    const int Y_OFFSET = 25;

    const auto getXPosition = [SCREEN_WIDTH] (sf::FloatRect textInfo) -> float {
        return SCREEN_WIDTH/2 - textInfo.width/2;
    };

    sf::Text startText = getText("start");
    sf::Text settingsText = getText("help");
    sf::Text exitText = getText("exit");

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

std::vector<sf::Text> getSettingsMenu() {
    std::vector<sf::Text> texts;

    const std::map<std::string, std::string> controlKeys = {
            {"left moving", config["MOVE_LEFT_KEY"]},
            {"right moving", config["MOVE_RIGHT_KEY"]},
            {"jump", config["JUMP_KEY"]},
            {"rage", config["RAGE_KEY"]},
            {"focus", config["FOCUS_KEY"]},
            {"light attack", config["LIGHT_ATTACK_KEY"]},
            {"heavy attack", config["HEAVY_ATTACK_KEY"]},
    };

    const float SETTING_X_POS = sf::VideoMode::getDesktopMode().width / 5;
    const float KEY_X_POS = SETTING_X_POS * 3.5f;

    const int BASE_OFFSET = 60;
    float iter = 0.f;

    for (const auto& [key, value] : controlKeys) {
        sf::Text keyText = getText(key);
        keyText.setPosition(SETTING_X_POS, iter * 100 + BASE_OFFSET);

        sf::Text valueText = getText(value);
        valueText.setPosition(KEY_X_POS, iter * 100 + BASE_OFFSET);

        texts.push_back(keyText);
        texts.push_back(valueText);

        iter++;
    }
    return texts;
}

void MainMenuMouseClickHandler(const sf::Event& event) {
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

void MainMenuEventsHandler(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        MainMenuMouseClickHandler(event);
    }
}

void HelpMenuEventsHandler(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        HelpMenuKeyHandler();
    }
}

void HelpMenuKeyHandler() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        curState = GameState::MAIN_MENU;
        updateBGSprite();
    }
}

void LoadScreenEventsHandler(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed) {
        LoadScreenClickHandler();
    }
}

void LoadScreenClickHandler() {
    globalTimer.restart();
    curState = GameState::GAME_PROCESS;
    updateBGSprite();
}

void GameEndClickHandler() {
    curState = GameState::MAIN_MENU;
    updateBGSprite();
}

void GameEndEventsHandler(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::KeyPressed) {
        GameEndClickHandler();
    }
}

void mouseEventsHandler(const sf::Event& event) {
    if (!(knyaz.isJump || knyaz.isFalling || knyaz.isMovingLeft || knyaz.isMovingRight)) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            knyaz.changeAnimation(animationContainer["easyAttack"]);
        } else if (event.mouseButton.button == sf::Mouse::Right) {
            knyaz.changeAnimation(animationContainer["heavyAttack"]);
        }
    }
}

void jumpHandler(const sf::Event& event) {
    if (knyaz.isJump && !(knyaz.isDoubleJump)) {
        knyaz.isDoubleJump = true;
        knyaz.changeAnimation(animationContainer["jump"]);
        knyaz.freeFallingTimer.restart();
    } else if (!knyaz.isJump && !knyaz.isDoubleJump) {
        knyaz.isJump = true;
        knyaz.changeAnimation(animationContainer["jump"]);
        knyaz.freeFallingTimer.restart();
    }
}

void movementHandler() {
    bool moveLeftPressed = sf::Keyboard::isKeyPressed(keymap["MOVE_LEFT_KEY"]);
    bool moveRightPressed = sf::Keyboard::isKeyPressed(keymap["MOVE_RIGHT_KEY"]);
    bool isKnyazStanding = !(knyaz.isJump || knyaz.isFalling);

    if (moveLeftPressed && !knyaz.isMovingLeft) {
        knyaz.isMovingLeft = true;
        if (isKnyazStanding) knyaz.changeAnimation(animationContainer["run"]);
        if (!knyaz.isLeftOrented) knyaz.isLeftOrented = true;

    } else if (!moveLeftPressed && knyaz.isMovingLeft) {
        knyaz.isMovingLeft = false;
        if (!knyaz.isMovingRight && isKnyazStanding) knyaz.changeAnimation(animationContainer["idle"]);

    } else if (moveRightPressed && !knyaz.isMovingRight) {
        knyaz.isMovingRight = true;
        if (isKnyazStanding) knyaz.changeAnimation(animationContainer["run"]);
        if (knyaz.isLeftOrented) knyaz.isLeftOrented = false;

    } else if (!moveRightPressed && knyaz.isMovingRight) {
        knyaz.isMovingRight = false;
        if (!knyaz.isMovingLeft && isKnyazStanding) knyaz.changeAnimation(animationContainer["idle"]);

    }
}

void GameProcessEventsHandler(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        mouseEventsHandler(event);
    }



    if (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(keymap["JUMP_KEY"])) {
        jumpHandler(event);
    }

    movementHandler();
}