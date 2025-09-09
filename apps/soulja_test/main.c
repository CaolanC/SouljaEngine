#include <soulja_shared/world_generation.h>

#include <stdio.h>

void print_array();

int main() {
    Chunk chunk = generate_cellular_chunk();
    print_array(chunk);
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
