#pragma once

#include <cstddef>
#include <SDL3/SDL.h>
#include <glad/glad.h>

namespace gfx
{

class Mesh
{
public:
    Mesh() {
        
    }

private:
    unsigned int vao{}, vbo{}, ebo{};
    std::size_t index_count{};
};

};
