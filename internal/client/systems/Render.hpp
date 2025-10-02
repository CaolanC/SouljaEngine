#pragma once

#include <entt/entt.hpp>
#include <core/MeshManager.hpp>
#include <core/Mesh.hpp>
#include "component/MeshRef.hpp"
#include <systems/RenderUtils.hpp>
#include <core/ShaderProgramManager.hpp>

namespace systems {
    void Render(entt::registry& reg, core::ShaderProgramManager programs, entt::entity camera) {
        core::MeshManager& mesh_manager = reg.ctx().get<component::mesh_manager>().manager;
        glm::mat4 projection = glm::perspective(glm::radians(60.0f), (float) INIT_SCREEN_WIDTH / (float) INIT_SCREEN_HEIGHT, 0.0f, 100.0f);
        glm::mat4 view_matrix = glm::inverse(reg.get<component::transform>(camera));

        auto& mesh_m = reg.ctx().get<component::mesh_manager>();
        auto view = reg.view<component::mesh_ref, component::mat_ref>();
        for (auto [e, mesh_ref, mat_ref]: view.each()) {
            core::Mesh mesh = mesh_manager.get_mesh(mesh_ref.id);
            unsigned int program = programs.get_program(mat_ref.id);

            systems::Utils::RenderUtils::set_view_mat(view_matrix, program);
            systems::Utils::RenderUtils::set_projection_mat(projection, program);

            mesh.bind_vao();
            glUseProgram(program);
            glDrawElements(
                GL_TRIANGLES,      // mode
                mesh.get_index_count(),    // count
                GL_UNSIGNED_INT,   // type
                (void*)0           // element array buffer offset
            );
        }
    }
}