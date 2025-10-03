#pragma once
#include <entt/entt.hpp>
#include <component/Core.hpp>
#include <string>
#include <systems/RenderUtils.hpp>
#include "tiny_gltf.h"
#include "glm/gtx/fast_trigonometry.hpp"

namespace systems {
    void MeshLoading(entt::registry& r) {
        auto& mm = r.ctx().get<component::mesh_manager>();

    }

    void CreateMesh(entt::registry& r, std::string p) {
        tinygltf::TinyGLTF loader;
        tinygltf::Model model;
        std::string err, warn;
        const bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, systems::Utils::RenderUtils::asset(p));

        if (!warn.empty()) {
            printf("WARN: %s\n", warn.c_str());
        }

        if (!err.empty()) {
            printf("ERR: %s\n", err.c_str());
        }

        if (!ret) {
            printf("Need to look in the repo for this message lol.\n.");
        }

        auto s = model.scenes.at(model.defaultScene);
        for (auto const& n: s.nodes) {
            std::cout << model.nodes[n].name << std::endl;
        }
    }
}
