#pragma once
#include <glm/mat4x4.hpp>

#include "glm/fwd.hpp"
#include "glm/detail/type_quat.hpp"
#include "glm/ext/matrix_transform.hpp"
#include <core/MeshManager.hpp>

namespace component
{
    using position = glm::vec3;

    using rotation = glm::quat;

    using transform = glm::mat4;

    struct camera {

    };

    struct free_movement_camera {

    };

    struct camera_attachment {

    };

    struct game_input {

    };

    struct keyboard_state {
        const bool* k_state;
        int no_keys;
    };

    struct mouse_state {
        float dx, dy;
    };

    struct user_control {};

    struct mesh_manager {
        core::MeshManager manager;
    };

}
