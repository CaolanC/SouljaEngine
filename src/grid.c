#include "internal/grid.h"

#include <stddef.h>

void init_grid(Grid* grid) {
    for(int i = 0; i < GRID_HEIGHT_LENGTH; i++) {
        for(int j = 0; j < GRID_HEIGHT_LENGTH; j++) {
            Cell cell;
            grid->cells[i][j] = cell;
        }
    }
}
