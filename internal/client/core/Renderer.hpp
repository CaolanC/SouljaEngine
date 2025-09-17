#pragma once

#include <core/Scene.hpp>
#include <core/defines.hpp>
#include <core/MeshManager.hpp>
#include <stdio.h>

namespace core
{
    class Renderer
    {
    public:
        void render(core::Scene scene, core::MeshManager meshes) {
            const std::vector<core::Object> objects = scene.get_objects();
            core::defines::MeshHandle curr_handle;

            for(auto obj : objects) {

                core::Mesh mesh = meshes.get_mesh(obj.get_mesh_handle());
                mesh.bind_vao();
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