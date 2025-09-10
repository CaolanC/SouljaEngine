#ifndef MOUSE_H
#define MOUSE_H

typedef struct {
    float x_delta;
    float y_delta;
} MouseState;

void update_mouse_state(MouseState* mouse_state, float x, float y);


MouseState make_mouse_state();

#endif
