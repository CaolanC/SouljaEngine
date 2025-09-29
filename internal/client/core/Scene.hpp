#pragma once

#include <core/Object.hpp>
#include <core/cameras/CameraBase.h>
#include <vector>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <entt/entt.hpp>

#include "EntityManager.hpp"
#include "component/Core.hpp"
#include "spawn/Spawn.hpp"
#include "systems/Render.hpp"
#include <core/MeshManager.hpp>
#include <core/sh_src.hpp>

#include <core/ShaderProgramManager.hpp>

#include "systems/Transform.hpp"

namespace core
{

class Scene
{
public:

    explicit Scene(core::cameras::IViewMatrix& iView) : camera(iView), view_matrix(camera.get_view_matrix()), entities(entt::registry()), e_manager(EntityManager()) {
        spawn_default_camera();
        spawn_triangle();
        cam = e_manager.spawn(spawn::freecam);
        //cam = spawn::freecam(entities);
    }

    void spawn_default_camera() {
        current_camera = spawn(spawn::freecam);
    }

    void spawn_triangle() {

        std::vector<float> vertices = {
            0.0f, 0.5f, -10.0f,
           -0.5f, 0.0f, -10.0f,
            0.0f, 0.0f, -10.0f
        };
        std::vector<unsigned int> indices = {
            0, 1, 2
        };

        core::MeshSerialiser mesh_serialiser(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        core::Mesh mesh(vertices, indices, mesh_serialiser);
        xg::Guid triangle_mesh_ref = mesh_manager.createIndexedMeshFromVertices(vertices, indices, mesh_serialiser);

        std::vector<core::ShaderSource> shader_sources = {
            core::sh_src::v3D(),
            core::sh_src::fSolid()
        };
        ShaderProgramHandle triangle_program_ref = programs.from_source_vec(shader_sources);

        spawn::triangle(std::ref(registry), triangle_mesh_ref, triangle_program_ref);

    }

    entt::entity spawn(std::function<entt::entity(entt::registry& registry)>const& spawn_function) {
        return spawn_function(std::ref(registry));
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

    void update_entities() {
        e_manager.update();
    }

    glm::mat4 get_camera_transform() {
        return e_manager.get_entity_transform(cam);
    }

    void set_camera_position(glm::vec3 position) {
        auto &pos = registry.get<component::position>(current_camera);
        pos = position;
    }

    entt::registry& get_registry() {
        return std::ref(entities);
    }

    void update() { // Call this once per frame
        systems::Transform(std::ref(registry));
        systems::Render(std::ref(registry), std::ref(mesh_manager), std::ref(programs), std::ref(current_camera));
    }

private:

    std::vector<core::Object> objects;
    core::cameras::IViewMatrix& camera;
    glm::mat4 view_matrix;
    entt::registry entities;
    entt::entity camera_attachment;
    entt::entity cam;
    core::EntityManager e_manager;
    entt::registry registry;
    core::MeshManager mesh_manager;
    entt::entity current_camera;
    core::ShaderProgramManager programs;
};

}
