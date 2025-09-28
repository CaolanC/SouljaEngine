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
            RunScript script = RunScript([this](){
                return 0;
            });
            push_frame_script(script);
        };
    };
}
