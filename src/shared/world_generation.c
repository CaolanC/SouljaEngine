#include <FastNoiseLite.h>
#include <stdio.h>

static void setup_noise() {
    fnl_state noise = fnlCreateState();
    noise.noise_type = FNL_NOISE_PERLIN;
}

typedef struct {
    float value;
} Cell;

typedef struct {
    Cell cell[64][64];
} Chunk;

Chunk make_chunk() {
    Chunk chunk = {0};
    return chunk;
}

Chunk generate_cellular_chunk() {
    Chunk chunk = make_chunk();
    fnl_state noise = fnlCreateState();
    noise.noise_type = FNL_NOISE_PERLIN;
    noise.frequency = 0.8f;
    
    for(int x = 0; x < 64; x++) {
        for(int y = 0; y < 64; y++) {
            float noise_value = fnlGetNoise2D(&noise, x, y);
            chunk.cell[x][y].value = noise_value;
        }
    }

    return chunk;
}

