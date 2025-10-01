#pragma once
#include <entt/entt.hpp>
#include <component/Core.hpp>
#include <iostream>

namespace systems {
    void PlayerControl(entt::registry& r) {
        const auto& kb = r.ctx().get<component::keyboard_state>();
        const auto& ms = r.ctx().get<component::mouse_state>();

        auto view = r.view<component::player_controllable, component::position>();

        for (auto [e, pos]: view.each()) {
            if (kb.k_state[SDL_SCANCODE_W]) {
                pos += glm::vec3(0, 0, -0.5);
            }
            if (kb.k_state[SDL_SCANCODE_S]) {
                pos += glm::vec3(0, 0, 0.5);
            }
        }

        std::cout << ms.dx << " " << ms.dy << std::endl;
    }
}
