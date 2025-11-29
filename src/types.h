#ifndef KNYAZ_GAME_TYPES_H
#define KNYAZ_GAME_TYPES_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>

enum class GameState {
    MAIN_MENU,
    HELP_MENU,
    LOAD_SCREEN_1,
    LOAD_SCREEN_2,
    GAME_PROCESS,
    GAME_END
};

enum class AnimationTypes {
    RUN,
    JUMP,
    FALL,
    ATTACK,
    IDLE
};

struct GameEntity {
    sf::RectangleShape body;
    float getTop() {
        return body.getPosition().y;
    }
    float getBot() {
        sf::Vector2f pos = body.getPosition();
        sf::Vector2f size = body.getSize();
        return pos.y + size.y;
    }
    float getLeft() {
        return body.getPosition().x;
    }
    float getRight() {
        sf::Vector2f pos = body.getPosition();
        sf::Vector2f size = body.getSize();
        return pos.x + size.x;
    }
};

//struct AnimationData {
//    sf::Texture animationTexture;
//    int animationFrames;
//    AnimationTypes animationType;
//};
//
//struct Knyaz : GameEntity {
//    bool isMovingLeft = false;
//    bool isMovingRight = false;
//    bool isJump = false;
//    bool isFalling = false;
//    bool isLeftOrented = false;
//
//    int animationFrameNumber;
//
//    sf::Clock freeFallingTimer;
//    sf::Clock animationTimer;
//
//    AnimationData animationData;
//
//    void animationProcess() {
//        if (animationTimer.getElapsedTime().asMilliseconds() < 100) return;
//        animationTimer.restart();
//
//        animationFrameNumber++;
//        animationFrameNumber %= animationData.animationFrames;
//
//        body.setTexture(&animationData.animationTexture);
//        if (isLeftOrented) {
//            body.setTextureRect(sf::IntRect(120 * animationFrameNumber + 27 + 43, 40, -43, 40));
//        } else {
//            if (animationData.animationType == AnimationTypes::ATTACK) {
//                body.setTextureRect(sf::IntRect(120 * animationFrameNumber + 53, 40, 65, 40));
//            } else {
//                body.setTextureRect(sf::IntRect(120 * animationFrameNumber + 27, 40, 43, 40));
//            }
//        }
//        body.setSize(sf::Vector2f(80.f, 80.f));
//    }
//
//    void changeAnimation(const AnimationData& newAnimation) {
//        animationData = newAnimation;
//        animationFrameNumber = 0;
//        animationTimer.restart();
//    }
//};

struct MainMenu {
    sf::Text startText;
    sf::FloatRect startTextInfo;
    sf::Text settingsText;
    sf::FloatRect settingsTextInfo;
    sf::Text exitText;
    sf::FloatRect exitTextInfo;
};

using SettingsMenu = std::vector<sf::Text>;

#endif //KNYAZ_GAME_TYPES_H