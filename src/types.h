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

enum class ObjsTypes {ENTITY, OBTACLE, SPIKES, SPIKES_UP, ENEMY, BOTTLE, WALL};

enum class EnemyStates {PATROLLING, AGRESSIVE};

#endif //KNYAZ_GAME_TYPES_H