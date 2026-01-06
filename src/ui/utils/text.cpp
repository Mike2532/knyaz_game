#include "../../globals/globals.h"

using namespace std;

sf::Text makeText(const string& textContent) {
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
