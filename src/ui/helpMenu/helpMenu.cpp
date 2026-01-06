#include <vector>
#include <map>
#include "../utils/text.h"
#include "../../../config/config.h"
#include "../../globals/globals.h"
#include "../../resources/BG/BG.h"

using namespace std;

using HelpMenu = std::vector<sf::Text>;

HelpMenu helpMenu;

vector<sf::Text> getHelpMenu() {
    std::vector<sf::Text> texts;

    const map<std::string, std::string> controlKeys = {
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
        sf::Text keyText = makeText(key);
        keyText.setPosition(SETTING_X_POS, iter * 100 + BASE_OFFSET);

        sf::Text valueText = makeText(value);
        valueText.setPosition(KEY_X_POS, iter * 100 + BASE_OFFSET);

        texts.push_back(keyText);
        texts.push_back(valueText);

        iter++;
    }
    return texts;
}

void helpMenuKeyHandler() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        curState = GameState::MAIN_MENU;
        updateBGSprite();
    }
}

void helpMenuEventsHandler(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        helpMenuKeyHandler();
    }
}