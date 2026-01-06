#ifndef KNYAZ_GAME_ANIMATIONS_H
#define KNYAZ_GAME_ANIMATIONS_H

extern sf::Texture KnyazIdleTexture;
extern sf::Texture KnyazRunTexture;
extern sf::Texture KnyazJumpTexture;
extern sf::Texture KnyazFallingTexture;
extern sf::Texture KnyazEasyAttackTexture;
extern sf::Texture KnyazHeavyAttackTexture;
extern sf::Texture KnyazDeathTexture;
extern sf::Texture KnyazWallHangTexture;

extern sf::Texture EnemyWalkTexture;
extern sf::Texture EnemyAttackTexture;
extern sf::Texture EnemyIDLETexture;

void initAnimationTextures();
void initAnimations();

#endif //KNYAZ_GAME_ANIMATIONS_H
