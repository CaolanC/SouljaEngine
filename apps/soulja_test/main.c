#include <soulja_shared/world_generation.h>

#include <stdio.h>

#define SJA_CHUNK_SIZE 64

void print_array();

int main() {
    int chunk[SJA_CHUNK_SIZE][SJA_CHUNK_SIZE][SJA_CHUNK_SIZE];
    return 0;
}

void print_array(Chunk chunk) {
    for(int x = 0; x < 64; x++) {
        for(int y = 0; y < 64; y++) {
            printf("%f ", chunk.cell[x][y].value);
        }
        printf("\n");
    }
}
