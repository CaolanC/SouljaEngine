#pragma once

#include <cstddef>
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <vector>

namespace core
{

class MeshSerialiser
{
public:
    int _location;
    GLint _vec_size;
    GLenum _vec_data_type;
    GLboolean _normalized_flag;
    int _stride;
    void* _offset;

    MeshSerialiser(
        int location, 
        GLint vec_size, 
        GLenum vec_data_type,
        GLboolean normalized_flag,
        int stride,
        void* offset
    )
    {
        _location = location;
        _vec_size = vec_size;
        _vec_data_type = vec_data_type;
        _normalized_flag = normalized_flag;
        _stride = stride;
        _offset = offset;
    }

};

class Mesh
{
public:
    Mesh(std::vector<float> vertices, std::vector<unsigned int> indices, core::MeshSerialiser serialiser) {
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        genVBO(vertices);
        genEBO(indices);
        setAttrib(serialiser);
        index_count = indices.size();
        glBindVertexArray(0);
    }

    std::size_t get_index_count() {
        return index_count;
    }

    void bind_vao() {
        glBindVertexArray(vao);
    }
private:
    void genVBO(std::vector<float> vertices) {
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    }

    void genEBO(std::vector<unsigned int> indices) {
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
    }
    void setAttrib(core::MeshSerialiser serialiser) {
        glVertexAttribPointer(serialiser._location, serialiser._vec_size, serialiser._vec_data_type, serialiser._normalized_flag, serialiser._stride, serialiser._offset);
        glEnableVertexAttribArray(serialiser._location);
    }

private:
    unsigned int vao{}, vbo{}, ebo{};
    std::size_t index_count{};
};

};
