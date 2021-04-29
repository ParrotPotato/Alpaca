#include <core/window.hh>
#include <core/input.hh>

#include <graphics/shader.hh>

#include <graphics/vertexattrib.hh>
#include <graphics/mesh.hh>
#include <graphics/renderer.hh>

#include <SDL2/SDL.h>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <iostream>
#include <filesystem>

#include <imgui.h>


int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    Window window("Main Window", 800, 600);
    window.set_clear_color(glm::vec3(0.050, 0.160, 0.4704));

    InputHandler input(window);
    input.escapequit = true;

    std::cout << "Opengl : " << glGetString(GL_VERSION) << "\n";
    std::cout << "Running: " << std::filesystem::current_path() << "\n";

    ShaderProgram program("shader/simple/shader.vs", "shader/simple/shader.fs");

    // used for creating a wigit for updating clear color
    float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    Mesh mesh;

    mesh.position.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
    mesh.position.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
    mesh.position.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
    mesh.normal.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
    mesh.normal.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
    mesh.normal.push_back(glm::vec3(0.0f, 0.0f, 1.0f));

    mesh.indices.push_back(0);
    mesh.indices.push_back(1);
    mesh.indices.push_back(2);

    SimpleRenderer simplerenderer(program);
    simplerenderer.add_mesh_to_render(mesh);

    while(window.isopen())
    {
        window.clear();

        input.update();

        { // bit of test code
            ImGui::ColorEdit3("Clear Color", color);
            glm::vec3 clear_color = glm::vec3(color[0], color[1], color[2]);
            window.set_clear_color(clear_color);
        }

        simplerenderer.draw();

        window.update();
    }

    return 0;
}