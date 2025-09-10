#include <FastNoiseLite.h>
#include <stdio.h>

static void setup_noise() {
    fnl_state noise = fnlCreateState();
    noise.noise_type = FNL_NOISE_PERLIN;
}

#define SJA_CHUNK_SIZE 64

typedef int Chunk[SJA_CHUNK_SIZE][SJA_CHUNK_SIZE][SJA_CHUNK_SIZE];

static void fill_chunk_depth();

static void generate_chunk(Chunk chunk) {
    fnl_state noise = fnlCreateState();
    noise.noise_type = FNL_NOISE_PERLIN;
    noise.frequency = 0.5f;
    
    for(int x = 0; x < SJA_CHUNK_SIZE; x++) {
        for(int z = 0; z < SJA_CHUNK_SIZE; z++) {
            unsigned int noise_value = (unsigned int) fnlGetNoise2D(&noise, x, z) * 100;
            printf("%d", noise_value);
            fill_chunk_depth(chunk, x, z, floor(noise_value), 1);
        }
    }
}

static void fill_chunk_depth(int chunk[SJA_CHUNK_SIZE][SJA_CHUNK_SIZE][SJA_CHUNK_SIZE], int x, int z, int to, int block) {
    for(int y = 0; y < to; y++) {
        chunk[x][z][y] = block;
    }
}
