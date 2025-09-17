#include <soulja_client_lib/mouse.h>

MouseState make_mouse_state() {
    MouseState mouse_state = {0};
    return mouse_state;
}

void update_mouse_state(MouseState* mouse_state, float x, float y) {
    mouse_state->x_delta = x;
    mouse_state->y_delta = y;
}
