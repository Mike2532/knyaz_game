#include <SFML/System/Vector2.hpp>
#include <vector>
#include "../bottle/bottle.h"

using namespace std;

vector<sf::Vector2f> bossBottlesCoords {
    {5010.f, 512.f + 117.f}, //p2
    {5175.f, 512.f + 117.f}, //p2
    {4794.f, 268.f + 115.f}, //p4
    {5355.f, 268.f + 115.f}, //p5
    {5010.f, 97.f + 115.f}, //p6
    {5175.f, 97.f + 115.f}, //p6
};

void spawnBossBottles() {
    for (auto &bottleCoords : bossBottlesCoords) {
        spawnBottle(bottleCoords);
    }
}
