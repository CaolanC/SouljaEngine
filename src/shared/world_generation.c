#include <FastNoiseLite.h>

static void setup_noise() {
    fnl_state noise = fnlCreateState();
    noise.noise_type = FNL_NOISE_CELLULAR;
}

void generate_chunk() {
    setup_noise();
}

