#include "../../globals/globals.h"
#include "../../../config/config.h"
#include "./uiStruct.h"
#include "../../knyaz/knyaz.h"

UI ui;

sf::Texture HpIndicatorTexture;

void initUITextures() {
    HpIndicatorTexture.loadFromFile(config["UI_TEXTURES_FOLDER"] + config["HP_INDICATOR_TEXTURE"]);
}

void initUI(pair<const int, const int> screenSize) {
    constexpr float UI_X_MULT = 0.97;
    constexpr float UI_Y_MULT = 0.78;
    constexpr float BAR_LENGTH = 10.f;
    constexpr float BAR_HEIGHT = 70.f;
    const auto X_OFFSET = static_cast<float>(screenSize.first * UI_X_MULT);
    const auto Y_OFFSET = static_cast<float>(screenSize.second * UI_Y_MULT);
    constexpr float SPACE_BETWEEN = 20.f;

    ui.focusOutline.setPosition({X_OFFSET, Y_OFFSET});
    ui.focusOutline.setSize({BAR_LENGTH, BAR_HEIGHT});
    ui.focusOutline.setOutlineThickness(3.f);
    ui.focusOutline.setOutlineColor(sf::Color::Black);

    ui.focusFill.setPosition({X_OFFSET, Y_OFFSET + BAR_HEIGHT});
    ui.focusFill.setSize({BAR_LENGTH, 0});
    ui.focusFill.setFillColor(sf::Color::Blue);

    ui.rageOutline.setPosition({X_OFFSET + SPACE_BETWEEN, Y_OFFSET});
    ui.rageOutline.setSize({BAR_LENGTH, BAR_HEIGHT});
    ui.rageOutline.setOutlineThickness(3.f);
    ui.rageOutline.setOutlineColor(sf::Color::Black);

    ui.rageFill.setPosition({X_OFFSET + SPACE_BETWEEN, Y_OFFSET + BAR_HEIGHT});
    ui.rageFill.setSize({BAR_LENGTH, 0});
    ui.rageFill.setFillColor(sf::Color::Red);
}

void updateUI() {
    constexpr float BAR_LENGTH = 10.f;
    constexpr float BAR_HEIGHT = 70.f;

    ui.focusFill.setSize({BAR_LENGTH, -BAR_HEIGHT * knyaz.focusCounter/knyaz.MAX_FOCUS_COUNTER});
    ui.rageFill.setSize({BAR_LENGTH, -BAR_HEIGHT * knyaz.rageCounter/knyaz.MAX_RAGE_COUNTER});
}