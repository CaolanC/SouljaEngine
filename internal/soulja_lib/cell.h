#ifndef CELL_H
#define CELL_H

#include "obstacle.h"
#include "floor_type.h"

typedef struct Cell {
    int altitude;
    Obstacle obstacle;
    FloorType floor;
} Cell;

#endif
