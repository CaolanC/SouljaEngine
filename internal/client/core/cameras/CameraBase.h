#pragma once

#include <core/Object.hpp>

namespace core::cameras
{
    class CameraBase : public core::Object
    {
        public:
        CameraBase() : Object() {

        };
    };

    class FreeCamera : public CameraBase
    {
        public:
        FreeCamera() : CameraBase() {
            // push_script([this]() {
            //     return 0;
            // });
        };
    };
}
