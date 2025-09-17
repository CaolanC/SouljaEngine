#pragma once

#include <core/Object.hpp>
#include <core/cameras/CameraBase.h>

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

private:

    std::vector<core::Object> objects;
    core::cameras::CameraBase camera;
};

}
