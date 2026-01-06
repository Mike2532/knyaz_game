#include "../../globals/globals.h"
#include "../../../config/config.h"

sf::Texture GroundTexture;
sf::Texture LavaTexture;
sf::Texture SpikesTexture;
sf::Texture SpikesUpTexture;
sf::Texture BottleTexture;

void initObjsTextures() {
    GroundTexture.loadFromFile(config["WORLD_TEXTURES_FOLDER"] + config["GROUND_TEXTURE"]);
    LavaTexture.loadFromFile(config["WORLD_TEXTURES_FOLDER"] + config["LAVA_TEXTURE"]);
    SpikesTexture.loadFromFile(config["WORLD_TEXTURES_FOLDER"] + config["SPIKES_TEXTURE"]);
    SpikesUpTexture.loadFromFile(config["WORLD_TEXTURES_FOLDER"] + config["SPIKES_UP_TEXTURE"]);
    BottleTexture.loadFromFile(config["WORLD_TEXTURES_FOLDER"] + config["BOTTLE_TEXTURE"]);
}