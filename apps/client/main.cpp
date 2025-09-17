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

using namespace core::defines;

void get_shader_source(const char* path, char* shader_buffer, size_t shader_buffer_length) {
    char tmp[512];
    strcpy(tmp, SLJA_ASSETS_DIR);
    strcat(tmp, path);
    FILE* stream = fopen(tmp, "r");
    if (stream == NULL) {
        printf("Shader source not loaded, check path.");
    }

    size_t bytes = fread(shader_buffer, 1, shader_buffer_length - 1, stream);
    shader_buffer[bytes] = '\0';
}


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
        MeshHandle triangle = meshes.createIndexedMeshFromVertices(vertices, indices, serialiser);
        
        core::Object triangle_object;
        triangle_object.set_mesh(triangle);
        scene.add_object(triangle_object);

        unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
        // Set up shaders
        char vertex_source[2048];
        get_shader_source("/shaders/triangle_vertex_sh.glsl", vertex_source, sizeof(vertex_source));
        const char* shader_src = vertex_source;
        glShaderSource(vertexShader, 1, &shader_src, NULL);
        glCompileShader(vertexShader);

        unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        char frag_source[2048];
        get_shader_source("/shaders/triangle_fragment_sh.glsl", frag_source, sizeof(frag_source));
        const char* frag_src = frag_source;
        glShaderSource(fragmentShader, 1, &frag_src, NULL);
        glCompileShader(fragmentShader);

        unsigned int shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);

        GLint ok; char log[1024];

        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &ok);
        if(!ok){ glGetShaderInfoLog(vertexShader, sizeof log, NULL, log); SDL_Log("VS: %s", log); }

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &ok);
        if(!ok){ glGetShaderInfoLog(fragmentShader, sizeof log, NULL, log); SDL_Log("FS: %s", log); }

        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &ok);
        if(!ok){ glGetProgramInfoLog(shaderProgram, sizeof log, NULL, log); SDL_Log("LINK: %s", log); }
        int w = INIT_SCREEN_WIDTH, h = INIT_SCREEN_HEIGHT;
        glViewport(0, 0, w, h);

        bool quit = false;
        SDL_Event event;
        while (!quit) {

            glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            
            renderer.render(scene, meshes);

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
