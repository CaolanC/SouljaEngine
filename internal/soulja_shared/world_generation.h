#ifndef WORLD_GENERATION_H
#define WORLD_GENERATION_H

#define FNL_IMPL

#include <FastNoiseLite.h>

static void setup_noise() {
    fnl_state noise = fnlCreateState();
    noise.noise_type = FNL_NOISE_CELLULAR;
}

typedef struct {
    float value;
} Cell;

typedef struct {
    Cell cell[64][64];
} Chunk;

Chunk make_chunk();

Chunk generate_cellular_chunk();


#endif
