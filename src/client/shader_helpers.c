#include <stdio.h>
#include <soulja_client_lib/config.h>
#include <string.h>

FILE* get_shader_source(const char* path) {
    char tmp[512];
    strcpy(tmp, SLJA_ASSETS_DIR);
    strcat(tmp, path);
    FILE* stream = fopen(tmp, "r");
    if (stream == NULL) {
        printf("Shader source not loaded, check path.");
    }
    return stream;
}
