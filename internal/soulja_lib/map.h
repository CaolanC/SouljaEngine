#ifndef MAP_H
#define MAP_H

#include "grid.h"
#include "macros.h"

typedef struct Map {
    Grid grids[MAP_HEIGHT_LENGTH][MAP_HEIGHT_LENGTH];
} Map;

Map make_map();

#endif
