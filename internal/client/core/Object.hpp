#pragma once

#include <core/Mesh.hpp>
#include <core/defines.hpp>

namespace core
{

    class RunScript {
        public:
        RunScript(std::function<int()> script) : script(script) {

        }

        int run() {
            int ret;
            try
            {
                ret = script();
                return ret;                
            }
            catch (const std::bad_function_call& e) {
                std::cout << e.what() << '\n';
            }
        };
        private:
        std::function<int()> script;
    };

    class Object
    {
public:
        Object() : renderable(false) {
            
        }

        void set_mesh(MeshHandle handle) {
            set_renderable();
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

        void run_frame_scripts() {
            for (auto script : scripts) {
                script.run();
            }
        }

        void set_renderable() {
            renderable = true;
        }

        void unset_renderable() {
            renderable = false;
        }

        bool is_renderable() {
            return renderable;
        }

        void push_script(RunScript script) {
            scripts.push_back(script);
        }

private:
    MeshHandle mesh_handle;
    ShaderProgramHandle program_handle;
    std::vector<RunScript> scripts;
    bool renderable;

    };
};