#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "map.h"

typedef struct GameState {
    Map map;
} GameState;

GameState make_gamestate();

#endif
