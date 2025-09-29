#pragma once
#include <glm/mat4x4.hpp>

#include "glm/fwd.hpp"
#include "glm/detail/type_quat.hpp"
#include "glm/ext/matrix_transform.hpp"

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
}
