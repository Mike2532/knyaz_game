#ifndef KNYAZ_GAME_BOSS_H
#define KNYAZ_GAME_BOSS_H

#include <SFML/Graphics/Texture.hpp>
#include <map>

using namespace std;

enum class bossTexturesKeys{attack0, attack1, death, idle, walk};
const vector<string> bossTexturesTexturesNames{"attack0.png", "attack1.png", "death.png", "idle.png", "walk.png"};
extern map<bossTexturesKeys, sf::Texture*> bossTextures;
void initBossTextures();

#endif //KNYAZ_GAME_BOSS_H
