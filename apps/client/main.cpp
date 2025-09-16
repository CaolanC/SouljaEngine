#include <cstddef>

#include <glad/glad.h>
#include <SDL3/SDL.h>

#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <soulja_client_lib/setup.h>

#define INIT_SCREEN_WIDTH 1920
#define INIT_SCREEN_HEIGHT 1080

int SJA_Setup_SDL(SDL_Window** window) {
    *window = SDL_CreateWindow("Soulja", INIT_SCREEN_WIDTH, INIT_SCREEN_WIDTH, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);


    SDL_SetWindowRelativeMouseMode(*window, true);

    return 0;
};

int SJA_Setup_GL(SDL_Window* window, SDL_GLContext glcontext) {
    glcontext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glcontext); 

    return 0;
}

namespace Platform {

class Window
{
public:
    Window(const char* name, unsigned int width, unsigned int height) {
        InitSDL();
        window = SDL_CreateWindow("Soulja", width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
        InitContext();
        InitGLAD();
        InitOptions();
    };

    ~Window() {
        SDL_GL_DestroyContext(glcontext);
        SDL_DestroyWindow(window);
    };
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    void swap() {
        SDL_GL_SwapWindow(window);
    };

private:
    SDL_Window* window;
    SDL_GLContext glcontext;

    void InitOptions() {
        SDL_GL_SetSwapInterval(1);
    }

    void InitSDL() {
        SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_VIDEO);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    };


    int InitGLAD() {
        if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
            SDL_Log("Failed to initialize GLAD");
            return -1;
        }
        return 0;
    }

    int InitContext() {
        glcontext = SDL_GL_CreateContext(window);
        SDL_GL_MakeCurrent(window, glcontext);

        return 0;
    }

};

}; // Platform namespace

namespace Core::Cameras
{
    class Camera
    {

    };

    class FreeCamera : Camera
    {
        
    };
}

namespace Core
{

class Mesh
{
public:

private:
    unsigned int vao{}, vbo{}, ebo{};
    std::size_t index_count{};
};

class MeshInstance
{
    unsigned int VAO, VBO;
};

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

class Scene
{
    Scene() {
        
    }
};

}; // Core namespace

class Client
{
public:

    Client() {
    }

    void run() {
        bool quit = false;
        SDL_Event event;
        while (!quit) {

            glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_EVENT_QUIT:
                        quit = 1;
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
