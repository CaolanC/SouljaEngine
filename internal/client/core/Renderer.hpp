#pragma once

#include <core/Scene.hpp>
#include <core/defines.hpp>
#include <core/MeshManager.hpp>
#include <core/ShaderProgramManager.hpp>
#include <stdio.h>

namespace core
{
    class Renderer
    {
    public:
        void render(core::Scene scene, core::MeshManager meshes, core::ShaderProgramManager programs) {
            const std::vector<core::Object> objects = scene.get_objects();
            MeshHandle curr_handle;

            for(auto obj : objects) {

                core::Mesh mesh = meshes.get_mesh(obj.get_mesh_handle());
                unsigned int program = programs.get_program(obj.get_program_handle());
                
                mesh.bind_vao();
                glUseProgram(program);
                glDrawElements(
                    GL_TRIANGLES,      // mode
                    mesh.get_index_count(),    // count
                    GL_UNSIGNED_INT,   // type
                    (void*)0           // element array buffer offset
                );
            }
        };
    };
}