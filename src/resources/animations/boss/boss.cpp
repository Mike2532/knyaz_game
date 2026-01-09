#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "../../../../config/config.h"
#include "./boss.h"

using namespace std;

map<bossTexturesKeys, sf::Texture*> bossTextures;

void initBossTextures() {
    for (int i = 0; i < bossTexturesTexturesNames.size(); i++) {

        auto key = static_cast<bossTexturesKeys>(i);
        auto textureName = bossTexturesTexturesNames[i];

        auto* curTexture = new sf::Texture;
        curTexture->loadFromFile(config["BOSS_TEXTIRES_FOLDER"] + textureName);

        bossTextures[key] = curTexture;
    }
}