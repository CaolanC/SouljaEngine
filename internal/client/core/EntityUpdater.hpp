#pragma once

#include <entt/entt.hpp>
#include <component/Core.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/quaternion.hpp"

namespace core {
    class EntityUpdater {
        EntityUpdater() {

        };
        ~EntityUpdater() = default;

        void update(entt::registry& r) {
            update_transform(r);
        }

        void update_transform(entt::registry& r) {
            auto view = r.view<component::transform, component::position, component::rotation>();
            for (auto [e, transform, position, rotation]: view.each()) {
                transform = glm::translate(glm::mat4(1.0f), position) * glm::toMat4(rotation);
            }
        }
    };
}
