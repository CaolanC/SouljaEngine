#include <cstddef>

#include <glad/glad.h>
#include <SDL3/SDL.h>

#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <core/cameras/CameraBase.h>
#include <platform/Window.hpp>
#include <core/Mesh.hpp>
#include <core/Scene.hpp>
#include <core/defines.hpp>
#include <vector>
#include <stdio.h>
#include <map>
#include <core/MeshManager.hpp>
#include <core/scenes/Renderer.hpp>
#include <core/ShaderProgramManager.hpp>
#include <core/sh_src.hpp>
#include <entt/entt.hpp>
#include <string>
#include <hv/requests.h>
#include <hv/HttpClient.h>

class Scene
{

public:
    Scene(const std::string _name) {
        name = _name;
    }

    void add_entity() {
        const auto entity = entities.create();
    }
private:
    entt::registry entities;
    std::string name;
};

void request_join() {
    hv::HttpClient cli;
    HttpRequest req;
    req.method = HTTP_GET;
    req.url = "http://127.0.0.1:30000/join";
    req.headers["Connection"] = "keep-alive";
    req.body = "This is a sync request.";
    req.timeout = 10;
    HttpResponse resp;
    int ret = cli.send(&req, &resp);
    if (ret != 0) {
        printf("request failed!\n");
    } else {
        printf("%d %s\r\n", resp.status_code, resp.status_message());
        printf("%s %s\n", resp.body.c_str(), resp.headers["Connection"].c_str());
    }    
};

class Client
{
public:

    Client() {
    }

    void run() {

        std::vector<Scene> scenes;

        core::Scene scene;

        std::vector<float> vertices = {
            0.0f, 0.5f, -0.0f,
           -0.5f, 0.0f, -3.0f,
            0.0f, 0.0f, -3.0f
        };
        std::vector<unsigned int> indices = {
            0, 1, 2
        };

        core::MeshSerialiser serialiser(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        core::Mesh mesh(vertices, indices, serialiser);
        core::MeshManager meshes;
        MeshHandle triangle_mesh = meshes.createIndexedMeshFromVertices(vertices, indices, serialiser);
        core::ShaderProgramManager programs;
        std::vector<core::ShaderSource> shader_sources = {
            core::sh_src::v3D(),
            core::sh_src::fSolid()
        };

        ShaderProgramHandle triangle_program = programs.from_source_vec(shader_sources);
        core::Object triangle_object;

        triangle_object.set_program(triangle_program);
        triangle_object.set_mesh(triangle_mesh);
        scene.add_object(triangle_object);

        core::cameras::FreeCamera free_cam;
        scene.add_object(free_cam);

        int w = INIT_SCREEN_WIDTH, h = INIT_SCREEN_HEIGHT;
        glViewport(0, 0, w, h);

        bool quit = false;
        SDL_Event event;
        core::Renderer renderer = core::Renderer(meshes, programs);
        while (!quit) {

            glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            renderer.render(scene);

            while (SDL_PollEvent(&event)) {
                switch(event.type) {
                    case SDL_EVENT_QUIT:
                        quit = true;
                        break;
                }
            }
            window.swap();
        };
    }
private:
    Platform::Window window = Platform::Window(SLJA_WINDOW_TITLE, 1920, 1080);
};

int main() {
    request_join();
    Client client;
    client.run();
    return 0;
};
 