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

        void set_mesh(MeshHandle handle) {
            mesh_handle = handle;
        }

        void set_program(ShaderProgramHandle handle) {
            program_handle = handle;
        }

        ShaderProgramHandle get_program_handle() {
            return program_handle;
        }

        MeshHandle get_mesh_handle() {
            return mesh_handle;
        }

private:
    MeshHandle mesh_handle;
    ShaderProgramHandle program_handle;

    };
};