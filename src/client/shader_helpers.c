#include <stdio.h>
#include <soulja_client_lib/config.h>
#include <string.h>
#include <stdlib.h>

void get_shader_source(const char* path, char* shader_buffer, size_t shader_buffer_length) {
    char tmp[512];
    strcpy(tmp, SLJA_ASSETS_DIR);
    strcat(tmp, path);
    FILE* stream = fopen(tmp, "r");
    if (stream == NULL) {
        printf("Shader source not loaded, check path.");
    }

    size_t bytes = fread(shader_buffer, 1, shader_buffer_length - 1, stream);
    shader_buffer[bytes] = '\0';
    printf("FUN: %s\n", shader_buffer);
}
