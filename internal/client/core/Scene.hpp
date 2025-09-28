#pragma once

#include <core/Object.hpp>
#include <core/cameras/CameraBase.h>
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <entt/entt.hpp>

namespace core
{

class Scene
{
public:

    explicit Scene(core::cameras::IViewMatrix& iView) : camera(iView), view_matrix(camera.get_view_matrix()) {

    }

    void add_object(core::Object object) {
        objects.insert(objects.begin(), object);
    }

    const std::vector<core::Object> get_objects() {
        return objects;
    }

    void set_camera(core::cameras::IViewMatrix& view) {
        camera = view;
        view_matrix = view.get_view_matrix();
    }

    const glm::mat4 get_view_matrix() const {
        return camera.get_view_matrix();
    }


private:

    std::vector<core::Object> objects;
    core::cameras::IViewMatrix& camera;
    glm::mat4 view_matrix;
    entt::registry entities;
};

}
