#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <soulja_client_lib/setup.h>

#define INIT_SCREEN_WIDTH 1920
#define INIT_SCREEN_HEIGHT 1080

int SJA_Setup_SDL(SDL_Window** window) {
    *window = SDL_CreateWindow("Soulja", INIT_SCREEN_WIDTH, INIT_SCREEN_WIDTH, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    SDL_SetWindowRelativeMouseMode(*window, true);

    return 0;
};

int SJA_Setup_GL(SDL_Window* window, SDL_GLContext glcontext) {
    glcontext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glcontext); 
}

int SJA_Setup_Glad() {
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        SDL_Log("Failed to initialize GLAD");
        return -1;
    }
    return 0;
}
