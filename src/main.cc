#include <core/window.hh>
#include <core/input.hh>

#include <graphics/shader.hh>

#include <graphics/vertexattrib.hh>
#include <graphics/mesh.hh>
#include <graphics/renderer.hh>
#include <graphics/camera.hh>

#include <graphics/texture.hh>

#include <SDL2/SDL.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <filesystem>

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>


void processInput(InputHandler &input)
{
    if(input.keyboard.keydown(SDLK_LSHIFT))
    {
        SDL_SetRelativeMouseMode(SDL_TRUE);
    }
    else
    {
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }
}

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    Window window("Main Window", 800, 600);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    // window is the SDL_Window*
    // context is the SDL_GLContext
    ImGui_ImplSDL2_InitForOpenGL(window.sdl_win, window.context);
    ImGui_ImplOpenGL3_Init();

    InputHandler input(window);
    input.escapequit = true;

    std::cout << "Opengl : " << glGetString(GL_VERSION) << "\n";
    std::cout << "Running: " << std::filesystem::current_path() << "\n";

    ShaderInfo shaderinfo = {true, true, true};
    ShaderProgram program("shader/simple/shader.vs", "shader/simple/shader.fs", shaderinfo);

    // Testing space for texture loading and unloading

    TextureResourceHandler::initialise();
    Texture texture = TextureResourceHandler::load_texture("texture/space.jpg");
    Texture texture2 = TextureResourceHandler::load_texture("texture/space.jpg");

    std::cout << "texture : " << texture.id << "\n";
    std::cout << "texture2: " << texture2.id << "\n";

    TextureResourceHandler::unload_texture(texture);
    TextureResourceHandler::unload_texture(texture2);

    Mesh mesh;
    Vertex vertex;

    vertex.position = glm::vec3(0.0f, 0.0f, -10.0f);
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertex.uv = glm::vec2(0.0f, 0.0f);

    mesh.vertices.push_back(vertex);

    vertex.position = glm::vec3(1.0f, 0.0f, -10.0f);
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertex.uv = glm::vec2(1.0f, 0.0f);

    mesh.vertices.push_back(vertex);

    vertex.position = glm::vec3(0.0f, 1.0f, -10.0f);
    vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
    vertex.uv = glm::vec2(0.0f, 1.0f);

    mesh.vertices.push_back(vertex);

    mesh.indices.push_back(0);
    mesh.indices.push_back(1);
    mesh.indices.push_back(2);

    mesh.model_mat = glm::scale(mesh.model_mat, glm::vec3(5.0f, 5.0f, 1.0f));

    SimpleRenderer simplerenderer(program, true);
    simplerenderer.add_mesh_to_render(mesh);

    
    DefaultCamera camera;

    glm::vec4 clear_color(0.2f, 0.3f, 0.4f, 1.0f);

    while(window.isopen())
    {
        window.clear();
        input.update();

        // NOTE(nitesh): newframe for imgui should be created after the input have been passed to it and before the data has
        // been rendered, don't know why but Imgui likes to throw assertion failed if done other wise

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window.sdl_win);
        ImGui::NewFrame();

        {
            ImGui::Begin("Debug");
            ImGui::ColorEdit3("clear color", glm::value_ptr(clear_color));
            ImGui::SliderFloat3("camera position", glm::value_ptr(camera.position), 0, 100);
            window.set_clear_color(clear_color);
            ImGui::End();
        }

        processInput(input);
        camera.update_camera_position(input);
        simplerenderer.view_matrix = camera.get_view_matrix();

        simplerenderer.draw();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window.update();
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_Quit();

    return 0;
}