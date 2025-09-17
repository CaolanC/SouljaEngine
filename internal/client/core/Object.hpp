#pragma once

#include <core/Mesh.hpp>
#include <core/defines.hpp>

namespace core
{
    class Object
    {
public:
        Object() {
            
        }

        void set_mesh(core::defines::MeshHandle handle) {
            mesh_handle = handle;
        }

        core::defines::MeshHandle get_mesh_handle() {
            return mesh_handle;
        }

private:
    core::defines::MeshHandle mesh_handle;

    };
};