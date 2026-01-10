#include <SFML/Graphics/Text.hpp>
#include "./globals/globals.h"

void drawMenu(const std::vector<sf::Text>& textToPrint) {
    for (const sf::Text& text : textToPrint) {
        window.draw(text);
    }
}
