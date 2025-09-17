#include <cstddef>

#include <glad/glad.h>
#include <SDL3/SDL.h>

#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <core/cameras/CameraBase.h>
#include <platform/Window.hpp>
#include <core/Mesh.hpp>
#include <core/Scene.hpp>
#include <core/defines.hpp>
#include <vector>
#include <stdio.h>
#include <map>
#include <core/MeshManager.hpp>
#include <core/Renderer.hpp>
#include <core/ShaderProgramManager.hpp>
#include <core/sh_src.hpp>

// void get_shader_source(const char* path, char* shader_buffer, size_t shader_buffer_length) {
//     char tmp[512];
//     strcpy(tmp, SLJA_ASSETS_DIR);
//     strcat(tmp, path);
//     FILE* stream = fopen(tmp, "r");
//     if (stream == NULL) {
//         printf("Shader source not loaded, check path.");
//     }

//     size_t bytes = fread(shader_buffer, 1, shader_buffer_length - 1, stream);
//     shader_buffer[bytes] = '\0';
// }


#define INIT_SCREEN_WIDTH 1920
#define INIT_SCREEN_HEIGHT 1080

class Client
{
public:

    Client() {
    }

    void run() {

        core::Scene scene;
        core::Renderer renderer;

        std::vector<float> vertices = {
            0.0f, 0.5f, 0.0f,
           -0.5f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f
        };
        std::vector<unsigned int> indices = {
            0, 1, 2
        };

        core::MeshSerialiser serialiser(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        core::Mesh mesh(vertices, indices, serialiser);
        core::MeshManager meshes;
        MeshHandle triangle_mesh = meshes.createIndexedMeshFromVertices(vertices, indices, serialiser);
        core::ShaderProgramManager programs;
        std::vector<core::ShaderSource> shader_sources = {
            core::sh_src::v3D(),
            core::sh_src::fSolid()
        };

        ShaderProgramHandle triangle_program = programs.from_source_vec(shader_sources);
        core::Object triangle_object;

        triangle_object.set_program(triangle_program);
        triangle_object.set_mesh(triangle_mesh);
        scene.add_object(triangle_object);

        int w = INIT_SCREEN_WIDTH, h = INIT_SCREEN_HEIGHT;
        glViewport(0, 0, w, h);

        bool quit = false;
        SDL_Event event;
        while (!quit) {

            glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            renderer.render(scene, meshes, programs);

            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_EVENT_QUIT:
                        quit = true;
                        break;
                }
            }
            window.swap();
        };
    }
private:
    Platform::Window window = Platform::Window(SLJA_WINDOW_TITLE, 1920, 1080);
};

int main() {
    Client client;
    client.run();
    return 0;
};
