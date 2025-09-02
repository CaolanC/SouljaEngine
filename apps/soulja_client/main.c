#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <GL/gl.h>

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

int main(int arc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
    if (result < 0) {
        SDL_Log("SDL_Init error: %s", SDL_GetError());
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // (macOS needs forward-compatible flag for core 3.2+)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);


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

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

    unsigned int VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(shaderProgram);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    while (!quit) {

        glClearColor(0, 255, 255, 0.8);
        glClear(GL_COLOR_BUFFER_BIT);

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
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);
    }

    SDL_Log("SDL3 shut down.");

    SDL_GL_DestroyContext(glcontext);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
