#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glad/glad.h>
#include <cglm/cglm.h>
#include <soulja_client_lib/shader_helpers.h>
#include <soulja_client_lib/config.h>
#include <soulja_client_lib/setup.h>
#include <FastNoiseLite.h>
#include <soulja_client_lib/camera.h>
#include <soulja_client_lib/mouse.h>
#include <soulja_client_lib/setup.h>

float* make_square();

#define INIT_SCREEN_WIDTH 1920
#define INIT_SCREEN_HEIGHT 1080

int main(int argc, char* argv[]) {
    SDL_Window* window;
    int res = SJA_Setup_SDL(&window);
    SDL_GLContext glcontext;
    SJA_Setup_GL(window, glcontext);
    SJA_Setup_Glad();

    if (res) {
        printf("Error setting up open_gl");
    }

    int w, h;
    SDL_GetWindowSizeInPixels(window, &w, &h);
    glViewport(0, 0, w, h);
    
    SDL_GL_SetSwapInterval(1);

    size_t no_vertices = 0;
    float* vertices = make_square(&no_vertices);
    float o_vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
    };

    unsigned int theVAO, posVBO;

    glGenVertexArrays(1, &theVAO);
    glBindVertexArray(theVAO);

    glGenBuffers(1, &posVBO);
    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glBufferData(GL_ARRAY_BUFFER, no_vertices * sizeof(float), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

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
    GLint ok; char log[1024];

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &ok);
    if(!ok){ glGetShaderInfoLog(vertexShader, sizeof log, NULL, log); SDL_Log("VS: %s", log); }

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &ok);
    if(!ok){ glGetShaderInfoLog(fragmentShader, sizeof log, NULL, log); SDL_Log("FS: %s", log); }

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &ok);
    if(!ok){ glGetProgramInfoLog(shaderProgram, sizeof log, NULL, log); SDL_Log("LINK: %s", log); }

    mat4 projection_matrix;
    glm_perspective(glm_rad(60.0f), (float) INIT_SCREEN_WIDTH / (float) INIT_SCREEN_HEIGHT, 0.1f, 100.0f, projection_matrix);

    glUseProgram(shaderProgram);

    unsigned int uProjectionLoc = glGetUniformLocation(shaderProgram, "uProjection");
    if (uProjectionLoc == -1) SDL_Log("WARN: uProjection not found");
    glUniformMatrix4fv(uProjectionLoc, 1, GL_FALSE, (const float*) projection_matrix);

    //mat4 model_matrix;
    //glm_mat4_identity(model_matrix);
    //glm_translate(model_matrix, (vec3){0.0f, 0.0f, -18.0f});

    unsigned int uModelLoc = glGetUniformLocation(shaderProgram, "uModel");
    if (uModelLoc == -1) SDL_Log("WARN: uModel not found");
    //glUniformMatrix4fv(uModelLoc, 1, GL_FALSE, (const float*) model_matrix);
    
    mat4 view_matrix;

    vec3 camera_position = {0.0f, 0.0f, 0.0f};
    glm_lookat(camera_position, (vec3) {0.0f, 0.0f, -18.0f}, (vec3) {0.0f, 1.0f, 0.0f}, view_matrix);

    unsigned int uViewLoc = glGetUniformLocation(shaderProgram, "uView");
    glUniformMatrix4fv(uViewLoc, 1, GL_FALSE, (const float*) view_matrix);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    SDL_Event event;
    int quit = 0;
    float triangle_rotation = 0.0f;
    
    glPointSize(5.0f);
    float relX = 0.0f;
    float relY = 0.0f;
    vec3 forward = {0.0f, 0.0f, -1.0f};
    Camera camera = make_camera(0.0f, 0.0f, 0.0f, 1.0f);
    MouseState mouse_state = make_mouse_state();
    while (!quit) {

        glClearColor(0.0f, 1.0f, 1.0f, 0.8f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(theVAO);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT: {
                    SDL_Log("SDL3 event quit");
                    quit = 1;
                    break;
                }
                case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED: {
                    int w, h;
                    SDL_GetWindowSizeInPixels(window, &w, &h);
                    glViewport(0, 0, w, h);
                    break;
                }
                case SDL_EVENT_MOUSE_MOTION: {
                    relX += event.motion.xrel;
                    relY += event.motion.yrel;
                    break;
                }
            }
        }

        update_mouse_state(&mouse_state, relX, relY);

        relX = 0.0f;
        relY = 0.0f;

        const bool* k_state = SDL_GetKeyboardState(NULL);

        update_camera_orientation_y(&camera, uViewLoc, mouse_state, k_state);

        mat4 modelA; glm_mat4_identity(modelA);
        glm_translate(modelA, (vec3){0.0f, 0.0f, -4.0f});
        glUniformMatrix4fv(uModelLoc, 1, GL_FALSE, (const float*) modelA);
        
        glDrawArrays(GL_TRIANGLES, 0, no_vertices / 3);

        mat4 modelB; glm_mat4_identity(modelB);
        glm_translate(modelB, (vec3){0.0f, 0.0f, 3.0f});
        
        // rotate the triangle
        vec3 axis = {0.0f, 1.0f, 0.0f};

        if (triangle_rotation > 2 * M_PI) {
            triangle_rotation = 0.0f;
        }

        triangle_rotation += 0.01f;

        float angle = triangle_rotation;
        versor quat1;
        glm_quatv(quat1, angle, axis);
        
        mat4 rotation;
        glm_quat_mat4(quat1, rotation);
        glm_mat4_mul(modelB, rotation, modelB);

        glUniformMatrix4fv(uModelLoc, 1, GL_FALSE, (const float*) modelB);
        
        glDrawArrays(GL_TRIANGLES, 0, no_vertices / 3);

        SDL_GL_SwapWindow(window);
    }

    SDL_Log("SDL3 shut down.");

    SDL_GL_DestroyContext(glcontext);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}

float* make_square(size_t* out_floats) {
    static const float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,

        -0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f
    };
    size_t bytes = sizeof(vertices);
    float* data = (float*)malloc(bytes);
    memcpy(data, vertices, bytes);
    *out_floats = bytes / sizeof(float);
    return data;
}
