#include "./gameEntity.h"

float GameEntity::getTop() {
    return body.getPosition().y;
}

float GameEntity::getBot() {
    sf::Vector2f pos = body.getPosition();
    sf::Vector2f size = body.getSize();
    return pos.y + size.y;
}

float GameEntity::getLeft() {
    return body.getPosition().x;
}

float GameEntity::getRight() {
    sf::Vector2f pos = body.getPosition();
    sf::Vector2f size = body.getSize();
    return pos.x + size.x;
}