#include <soulja_client_lib/camera.h>
#include <soulja_client_lib/mouse.h>

#include <cglm/cglm.h>
#include <SDL3/SDL.h>
//#include <SDL3/SDL_main.h>
#include <glad/glad.h>

void update_camera_orientation_y(Camera* camera, int uViewLoc, MouseState mouse_state, const bool* k_state) {

    const float sensitivity = 0.002f;
    float yaw = -mouse_state.x_delta * sensitivity;
    float pitch = -mouse_state.y_delta * sensitivity;

    versor qYaw;
    glm_quatv(qYaw, yaw, (vec3) {0, 1, 0});
    versor qPitch;
    glm_quatv(qPitch, pitch, (vec3) {1, 0, 0});
    
    versor tmp;
    glm_quat_mul(qYaw, camera->orientation, tmp);
    glm_quat_mul(tmp, qPitch, camera->orientation);
    glm_quat_normalize(camera->orientation);

    vec3 fwd   = { 0.0f, 0.0f,-1.0f };
    vec3 right = { 1.0f, 0.0f, 0.0f };
    vec3 up    = { 0.0f, 1.0f, 0.0f };

    glm_quat_rotatev(camera->orientation, fwd, fwd);
    glm_quat_rotatev(camera->orientation, right, right);
    glm_quat_rotatev(camera->orientation, up, up);

    float move_speed = 0.1f;

    if (k_state[SDL_SCANCODE_W]) glm_vec3_muladds(fwd, move_speed, camera->position);
    if (k_state[SDL_SCANCODE_S]) glm_vec3_muladds(fwd, -move_speed, camera->position);

    if (k_state[SDL_SCANCODE_D]) glm_vec3_muladds(right, move_speed, camera->position);
    if (k_state[SDL_SCANCODE_A]) glm_vec3_muladds(right, -move_speed, camera->position);

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

Camera make_camera(float x, float y, float z, float speed) {
    Camera camera;
    camera.position[0] = x;
    camera.position[1] = y;
    camera.position[2] = z;
    camera.speed = speed;
    glm_quat_identity(camera.orientation);
    camera.y_rotation = 0.0f; // Has the range of 0 to 2 PI then we come back to 0;
    camera.y_axis[0] = 0;
    camera.y_axis[1] = 1;
    camera.y_axis[2] = 0;
    camera.x_axis[0] = 1;
    camera.x_axis[1] = 0;
    camera.x_axis[2] = 0;

    return camera;
};

