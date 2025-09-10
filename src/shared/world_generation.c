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
    int x;
    int z;
} Chunk;

Chunk make_chunk() {
    Chunk chunk = {0};
    return chunk;
}

typedef struct {
    int x;
    int y;
    int z;
} Vertice;

void chunk_to_vertices(Chunk chunk, Vertice vertices_buffer[64][64]) {

    for(int x = chunk.x; x++; x < 64) {
        for(int z = chunk.z; z++; z < 64) {
            vertices_buffer[x][z].x = x;
            vertices_buffer[x][z].y = chunk.cell[x][z].value;
            vertices_buffer[x][z].z = z;
        }
    }
}

void vertices_to_float_array(Vertice vertices[64][64], float arr[64*64*3]) {
    for(int x = 0; x < 64; x++) {
        for(int y = 0; y < 64; y++) {
        }
    }
}

void vertices_to_vbo(Vertice vertices[64][64], unsigned int vbo) {
    //glBindBuffer(GL_ARRAY_BUFFER, vbo);
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

void get_chunk_vertices(int x, int z, Vertice vertices[64][64]) {

    fnl_state noise = fnlCreateState();
    noise.noise_type = FNL_NOISE_PERLIN;
    noise.frequency = 0.8f;

    for(int _x = x; _x < 64; _x++) {
        for(int _z = z; _z < 64; _z++) {
            Vertice vertice;
            vertice.x = _x;
            vertice.z = _z;
            vertice.y = fnlGetNoise2D(&noise, _x, _z);
            vertices[_x][_z] = vertice;
        }
    }
}
