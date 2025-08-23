#ifndef GRID_H
#define GRID_H

#include "cell.h"
#include "macros.h"

typedef struct Grid {
    Cell cells[GRID_HEIGHT_LENGTH][GRID_HEIGHT_LENGTH];
} Grid;

void init_grid(Grid* grid);

#endif
