#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glad/glad.h>
#include <cglm/cglm.h>

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 uProjection;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = uProjection * vec4(aPos, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
    "}\0";

int train2();

int main(int arc, char* argv[]) {
    train2();
    return 0;
}

int train2() {
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    SDL_Window* window = SDL_CreateWindow("Train", 800, 800, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_GLContext glcontext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glcontext); 

    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        SDL_Log("Failed to initialize GLAD");
        return -1;
    }

    int w, h;
    SDL_GetWindowSizeInPixels(window, &w, &h);
    glViewport(0, 0, w, h);
    
    SDL_GL_SetSwapInterval(1);

    float vertices[] = {
        -0.5f, -0.5f, -14.0f,
         0.5f, -0.5f, -14.0f,
        -0.5f,  0.5f, -14.0f,
    };

    unsigned int theVAO, posVBO;

    glGenVertexArrays(1, &theVAO);
    glBindVertexArray(theVAO);

    glGenBuffers(1, &posVBO);
    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    GLint ok; char log[1024];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &ok);
    if(!ok){ glGetShaderInfoLog(vertexShader, sizeof log, NULL, log); SDL_Log("VS: %s", log); }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &ok);
    if(!ok){ glGetShaderInfoLog(fragmentShader, sizeof log, NULL, log); SDL_Log("FS: %s", log); }

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &ok);
    if(!ok){ glGetProgramInfoLog(shaderProgram, sizeof log, NULL, log); SDL_Log("LINK: %s", log); }

    mat4 projection_matrix;
    glm_perspective(glm_rad(60.0f), (float) 800 / (float) 800, 0.1f, 100.0f, projection_matrix);

    glUseProgram(shaderProgram);

    unsigned int uProjectionLoc = glGetUniformLocation(shaderProgram, "uProjection");
    if (uProjectionLoc == -1) SDL_Log("WARN: uProjection not found");
    glUniformMatrix4fv(uProjectionLoc, 1, GL_FALSE, (const float*) projection_matrix);
    


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    SDL_Event event;
    int quit = 0;
    while (!quit) {

        glClearColor(0.0f, 1.0f, 1.0f, 0.8f);
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
                case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED: {
                    int w, h;
                    SDL_GetWindowSizeInPixels(window, &w, &h);
                    glViewport(0, 0, w, h);
                    break;
                }
            }
        }
        glUseProgram(shaderProgram);
        glBindVertexArray(theVAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);
    }

    SDL_Log("SDL3 shut down.");

    SDL_GL_DestroyContext(glcontext);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
