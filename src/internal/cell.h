#ifndef CELL_H
#define CELL_H

#include "obstacle.h"

typedef struct Cell {
    int altitude;
    Obstacle obstacle;
} Cell;

#endif
