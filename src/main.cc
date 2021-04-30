#include <core/window.hh>
#include <core/input.hh>

#include <graphics/shader.hh>

#include <graphics/vertexattrib.hh>
#include <graphics/mesh.hh>
#include <graphics/renderer.hh>

#include <SDL2/SDL.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <filesystem>

#include <imgui.h>


int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    Window window("Main Window", 800, 600);

    InputHandler input(window);
    input.escapequit = true;

    std::cout << "Opengl : " << glGetString(GL_VERSION) << "\n";
    std::cout << "Running: " << std::filesystem::current_path() << "\n";

    ShaderInfo shaderinfo = {true, true, true};
    ShaderProgram program("shader/simple/shader.vs", "shader/simple/shader.fs", shaderinfo);

    // used for creating a wigit for updating clear color

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


    glm::vec4 clear_color(0.2f, 0.3f, 0.4f, 1.0f);
    glm::vec3 view_pos(0.0f, 0.0f, 0.0f);
    while(window.isopen())
    {
        window.clear();

        input.update();

        { // bit of test code
            ImGui::ColorEdit3("Clear Color", glm::value_ptr(clear_color));
            ImGui::SliderFloat3("Position", glm::value_ptr(view_pos), -10.0f, 10.0f);
            window.set_clear_color(clear_color);
            simplerenderer.view_matrix = glm::translate(glm::mat4(1.0f), view_pos);
        }

        simplerenderer.draw();

        window.update();
    }

    return 0;
}