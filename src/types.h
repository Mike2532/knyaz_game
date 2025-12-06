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
    IDLE,
    DEATH,
    CLIMB
};

enum class ObjsTypes {ENTITY, OBTACLE, SPIKES, SPIKES_UP, ENEMY};

enum class EnemyStates {PATROLLING, AGRESSIVE};

struct GameEntity {
    sf::RectangleShape body;
    ObjsTypes type;
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