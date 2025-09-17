#pragma once

#include <core/Mesh.hpp>
#include <core/defines.hpp>
#include <map>

namespace core {

class MeshManager
{
public:
    MeshHandle createIndexedMeshFromVertices(std::vector<float> vertices, std::vector<unsigned int> indices, core::MeshSerialiser serialiser) {
        core::Mesh mesh(vertices, indices, serialiser);
        auto id = nextID++;
        mesh_map.insert({id, mesh});
        return id;
    };

    void add_mesh(core::Mesh mesh) {
        mesh_map.insert({nextID++, mesh});
    }

    core::Mesh get_mesh(MeshHandle id) {
        return mesh_map.at(id);
    }

private:
    MeshHandle nextID{1};
    std::map<MeshHandle, core::Mesh> mesh_map;

};

}