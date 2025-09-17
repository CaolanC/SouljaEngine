#include <cstddef>

#include <glad/glad.h>
#include <SDL3/SDL.h>

#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <core/cameras/CameraBase.h>
#include <platform/Window.hpp>
#include <gfx/Mesh.hpp>
#include <core/scenes/BaseScene.hpp>

#define INIT_SCREEN_WIDTH 1920
#define INIT_SCREEN_HEIGHT 1080

using MeshHandle = uint32_t;

class MeshManager
{
public:
    MeshHandle createMesh() {
        return nextID++;
    };

private:
    MeshHandle nextID{1};

};

class Client
{
public:

    Client() {
    }

    void run() {

        float vertices[] = {
            0.0f, 0.5f, 0.0f,
           -0.5f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f
        };

        int indices[] = {
            0, 1, 2
        };

        unsigned int vbo, vao, ebo;

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glGenVertexArrays(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
        glEnableVertexAttribArray(0);

        bool quit = false;
        SDL_Event event;
        while (!quit) {

            glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

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
