//
// Created by cochrac2 on 29/09/2025.
//

#pragma once
#include <entt/entt.hpp>
#include <component/Core.hpp>
namespace spawn {
    // static entt::entity freecam(entt::registry& registry) {
    //     const auto entity = registry.create();
    //     registry.emplace<component::camera>(entity);
    //     registry.emplace<component::position>(entity, glm::vec3(0, 0, 0));
    //     registry.emplace<component::rotation>(entity, glm::quat());
    //     registry.emplace<component::transform>(entity, glm::mat4(1.0f));
    //     return entity;
    // }
    static entt::entity freecam(entt::registry& registry) {
        const auto entity = registry.create();
        registry.emplace<component::camera>(entity);
        registry.emplace<component::position>(entity, glm::vec3(0, 0, 0));
        registry.emplace<component::rotation>(entity, glm::quat());
        registry.emplace<component::transform>(entity, glm::mat4(1.0f));
        return entity;
    }
};
