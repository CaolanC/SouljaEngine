#pragma once
#include <cstddef>

#ifndef INIT_SCREEN_WIDTH
#define INIT_SCREEN_WIDTH 1920
#endif

#ifndef INIT_SCREEN_HEIGHT
#define INIT_SCREEN_HEIGHT 1080
#endif

#ifndef SLJA_ASSETS_DIR
#define SLJA_ASSETS_DIR NULL
#endif

using MeshHandle = unsigned int;
using ShaderProgramHandle = unsigned int;

enum ShaderType {
    Vertex  = GL_VERTEX_SHADER,
    Fragment = GL_FRAGMENT_SHADER
};