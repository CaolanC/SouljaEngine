#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <glad/glad.h>
#include <cglm/cglm.h>

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 uProjection;\n"
    "uniform mat4 uModel;\n"
    "uniform mat4 uView;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
    "}\0";

typedef struct {
    unsigned int vao, vbo;
} Mesh;

typedef struct {
    vec3 position;
    Mesh* mesh;
} GameObject;


typedef struct {
    vec3 position;
    versor orientation;
    vec3 y_axis;
    vec3 x_axis;
    uint speed;
    float y_rotation;
} Camera;

void update_camera_orientation_y(Camera* camera, int uViewLoc, const float mouse_movement_x, const float mouse_movement_y) {

    const float sensitivity = 0.002f;
    float y_rotation_delta = -mouse_movement_x * sensitivity;
    float x_rotation_delta = -mouse_movement_y * sensitivity;

    versor yaw;
    glm_quatv(yaw, y_rotation_delta, camera->y_axis);
    versor pitch;
    glm_quatv(pitch, x_rotation_delta, camera->x_axis);
    
    versor tmp;
    glm_quat_mul(yaw, camera->orientation, tmp);
    glm_quat_mul(tmp, pitch, camera->orientation);
    glm_quat_normalize(camera->orientation);

    versor quat_conj;
    glm_quat_conjugate(camera->orientation, quat_conj);

    mat4 rotation;
    glm_quat_mat4(quat_conj, rotation);

    mat4 trans;
    glm_translate_make(trans, (vec3){-camera->position[0], -camera->position[1], -camera->position[2]});
    
    mat4 new_view;
    glm_mat4_mul(rotation, trans, new_view);

    glUniformMatrix4fv(uViewLoc, 1, GL_FALSE, (const float*) new_view);

}

GameObject go_makeTriangle(vec3 position_xyz) {
    GameObject triangle;
    triangle.position[0] = position_xyz[0];
    triangle.position[1] = position_xyz[1];
    triangle.position[2] = position_xyz[2];
}

Camera make_camera(float x, float y, float z, float speed) {
    Camera camera;
    camera.position[0] = x;
    camera.position[1] = y;
    camera.position[2] = z;
    camera.speed = speed;
    camera.orientation[0] = 0;
    camera.orientation[1] = 1;
    camera.orientation[2] = 0;
    camera.y_rotation = 0.0f; // Has the range of 0 to 2 PI then we come back to 0;
    camera.y_axis[0] = 0;
    camera.y_axis[1] = 1;
    camera.y_axis[2] = 0;
    camera.x_axis[0] = 1;
    camera.x_axis[1] = 0;
    camera.x_axis[2] = 0;

    return camera;
};

int main() {
    SDL_Init(SDL_INIT_AUDIO | SDL_INIT_EVENTS | SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

    SDL_Window* window = SDL_CreateWindow("Train", 800, 800, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_GLContext glcontext = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, glcontext); 
    SDL_SetWindowRelativeMouseMode(window, true);

    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        SDL_Log("Failed to initialize GLAD");
        return -1;
    }

    int w, h;
    SDL_GetWindowSizeInPixels(window, &w, &h);
    glViewport(0, 0, w, h);
    
    SDL_GL_SetSwapInterval(1);

    float vertices[] = {
        -0.5f, -0.5f, -1.0f,
         0.5f, -0.5f, -1.0f,
        -0.5f,  0.5f, -1.0f,
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

    mat4 model_matrix;
    glm_mat4_identity(model_matrix);
    glm_translate(model_matrix, (vec3){0.0f, 0.0f, -18.0f});

    unsigned int uModelLoc = glGetUniformLocation(shaderProgram, "uModel");
    if (uModelLoc == -1) SDL_Log("WARN: uModel not found");
    glUniformMatrix4fv(uModelLoc, 1, GL_FALSE, (const float*) model_matrix);
    
    mat4 view_matrix;

    vec3 camera_position = {0.0f, 0.0f, 0.0f};
    glm_lookat(camera_position, (vec3) {0.0f, 0.0f, -18.0f}, (vec3) {0.0f, 1.0f, 0.0f}, view_matrix);

    unsigned int uViewLoc = glGetUniformLocation(shaderProgram, "uView");
    glUniformMatrix4fv(uViewLoc, 1, GL_FALSE, (const float*) view_matrix);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    SDL_Event event;
    int quit = 0;
    float x = 0.0f;
    float z = 0.0f;
    float hor = 0.0f;
    float ver = 0.0f;
    float y_rot = 0.0f;
    float mouse_x = 0.0f;
    float mouse_x_delta = 0.0f;
    float mouse_y = 0.0f;
    float mouse_y_delta = 0.0f;
    float triangle_rotation = 0.0f;
    float camera_rotation_y = 0.0f;

    vec3 forward = {0.0f, 0.0f, -1.0f};
    Camera camera = make_camera(0.0f, 0.0f, 0.0f, 1.0f);
    while (!quit) {

        glClearColor(0.0f, 1.0f, 1.0f, 0.8f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(theVAO);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    SDL_Log("SDL3 event quit");
                    quit = 1;
                    break;
                case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED: {
                    int w, h;
                    SDL_GetWindowSizeInPixels(window, &w, &h);
                    glViewport(0, 0, w, h);
                    break;
                }
            }
        }
        SDL_GetRelativeMouseState(&mouse_x_delta, &mouse_y_delta);

        vec3 camera_axis = {0.0f, 1.0f, 0.0f};
        versor quat;
        glm_quatv(quat, camera_rotation_y, camera_axis);
        mat4 camera_rotation;
        //glm_quat_mat4(quat, camera_rotation, quat);
        


        const bool* k_state = SDL_GetKeyboardState(NULL);
        if (k_state[SDL_SCANCODE_W]) z -= camera.speed;
        if (k_state[SDL_SCANCODE_S]) z += camera.speed;
        if (k_state[SDL_SCANCODE_A]) x -= camera.speed;
        if (k_state[SDL_SCANCODE_D]) x += camera.speed;

        update_camera_orientation_y(&camera, uViewLoc, mouse_x_delta, mouse_y_delta);

        mat4 modelA; glm_mat4_identity(modelA);
        glm_translate(modelA, (vec3){0.0f, 0.0f, -4.0f});
        glUniformMatrix4fv(uModelLoc, 1, GL_FALSE, (const float*) modelA);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);

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
        
        glDrawArrays(GL_TRIANGLES, 0, 3);

        SDL_GL_SwapWindow(window);
    }

    SDL_Log("SDL3 shut down.");

    SDL_GL_DestroyContext(glcontext);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}

