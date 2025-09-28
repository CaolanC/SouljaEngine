#pragma once

#include <core/Scene.hpp>
#include <core/defines.hpp>
#include <core/MeshManager.hpp>
#include <core/ShaderProgramManager.hpp>
#include <stdio.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp> 
#include <vector>


namespace core
{
    class Renderer
    {
    public:
        void render(core::Scene scene, core::MeshManager meshes, core::ShaderProgramManager programs) {
            const std::vector<core::Object> objects = scene.get_objects();
            MeshHandle curr_handle;

            for(auto obj : objects) {
                if (obj.is_renderable()) {
                    render_object(obj, meshes, programs);
                }

                obj.run_frame_scripts(); // Scripts that run every frame
            }
        
        };
    

        void render_object(core::Object obj, core::MeshManager meshes, core::ShaderProgramManager programs) {
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

    glm::mat4 camera() {
        glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float) INIT_SCREEN_WIDTH / (float) INIT_SCREEN_HEIGHT, 0.0f, 100.0f);

        // glUseProgram(shaderProgram);

        // unsigned int uProjectionLoc = glGetUniformLocation(shaderProgram, "uProjection");
        // if (uProjectionLoc == -1) SDL_Log("WARN: uProjection not found");
        //     glUniformMatrix4fv(uProjectionLoc, 1, GL_FALSE, (const float*) projection);
            
        };

        private:
            glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float) INIT_SCREEN_WIDTH / (float) INIT_SCREEN_HEIGHT, 0.0f, 100.0f);
            unsigned int shaderProgram;
    };
}
