#pragma once

#include <core/Mesh.hpp>
#include <core/defines.hpp>
#include <map>

namespace core {

class MeshManager
{
public:
    core::defines::MeshHandle createIndexedMeshFromVertices(std::vector<float> vertices, std::vector<unsigned int> indices, core::MeshSerialiser serialiser) {
        core::Mesh mesh(vertices, indices, serialiser);
        auto id = nextID++;
        mesh_map.insert({id, mesh});
        return id;
    };

    void add_mesh(core::Mesh mesh) {
        mesh_map.insert({nextID++, mesh});
    }

    core::Mesh get_mesh(core::defines::MeshHandle id) {
        return mesh_map.at(id);
    }

private:
    core::defines::MeshHandle nextID{1};
    std::map<core::defines::MeshHandle, core::Mesh> mesh_map;

};

}