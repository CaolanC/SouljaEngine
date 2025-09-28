#pragma once

#include <core/Object.hpp>
#include <core/cameras/CameraBase.h>
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace core
{

class Scene
{
public:

    Scene() {
        
    }

    void add_object(core::Object object) {
        objects.insert(objects.begin(), object);
    }

    const std::vector<core::Object> get_objects() {
        return objects;
    }

    void set_camera(core::cameras::CameraBase cam) {
        glm::vec3 camera_position = glm::vec3(0.0f, 0.0f, 0.0f);
        camera = cam;
        view_matrix = glm::lookAt(camera_position, glm::vec3(0.0f, 0.0f, -18.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    const glm::mat4& get_view_matrix() {
        return std::ref(view_matrix);
    }



private:

    std::vector<core::Object> objects;
    core::cameras::CameraBase camera;
    glm::mat4 view_matrix;
};

}
