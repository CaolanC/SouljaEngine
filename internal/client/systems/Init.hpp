#pragma once

#include <entt/entt.hpp>

#include <systems/MeshLoading.hpp>

namespace systems {
    void Init(entt::registry& r) {
        // Basically we want to be able to load a model from memory and see it
        systems::CreateMesh(r, "models/fox.gltf");
    }
}
