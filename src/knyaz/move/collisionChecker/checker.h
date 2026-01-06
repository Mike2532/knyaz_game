#ifndef KNYAZ_GAME_CHECKER_H
#define KNYAZ_GAME_CHECKER_H

bool isKnyazVerticalOverlap(GameEntity entity);
bool isLeftCollision(GameEntity& entity);
bool isRightCollision(GameEntity& entity);
bool isUpCollision(GameEntity& entity);
bool isDownCollision(GameEntity& entity);
bool isKnyazUpper(GameEntity& entity);
bool isKnyazLower(GameEntity& entity);
void checkKnyazEnemyCollision();

#endif //KNYAZ_GAME_CHECKER_H
