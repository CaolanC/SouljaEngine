#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <GL/gl.h>

int main(int arc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    if (result < 0) {
        SDL_Log("SDL_Init error: %s", SDL_GetError());
        return -1;
    }

    window = SDL_CreateWindow("Soulja", 800, 600, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        SDL_Log("SDL_CreateWindow: %s", SDL_GetError());
        return -2;
    }

    SDL_GLContext glcontext = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);

    SDL_Event event;
    int quit = 0;
    glViewport(0, 0, 800, 600);
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    SDL_Log("SDL3 event quit");
                    quit = 1;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    SDL_Log("KEYBOARD: %s", SDL_GetScancodeName(event.key.scancode));
                    break;
                case SDL_EVENT_WINDOW_RESIZED:
                    glViewport(0, 0, event.window.data1, event.window.data2);
                    break;
            }
        }
        glClearColor(0, 255, 255, 0.8);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    }

    SDL_Log("SDL3 shut down.");

    SDL_GL_DestroyContext(glcontext);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
