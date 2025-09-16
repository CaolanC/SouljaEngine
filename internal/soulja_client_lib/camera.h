#ifndef CAMERA_H
#define CAMERA_H

#include <cglm/cglm.h>
#include <SDL3/SDL.h>
#include <soulja_client_lib/mouse.h>

typedef struct {
    vec3 position;
    versor orientation;
    vec3 y_axis;
    vec3 x_axis;
    unsigned int speed;
    float y_rotation;
} Camera;

void update_camera_orientation_y(Camera* camera, int uViewLoc, MouseState mouse_state, const bool* k_state);

Camera make_camera(float x, float y, float z, float speed);

#endif
