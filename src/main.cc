#include <core/window.hh>
#include <core/input.hh>

#include <graphics/shader.hh>

#include <graphics/vertexattrib.hh>
#include <graphics/mesh.hh>
#include <graphics/renderer.hh>
#include <graphics/camera.hh>

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


void processInput(InputHandler &input, DefaultCamera &camera, SimpleRenderer &renderer)
{
    static float imm_mouse_sensitivity = 0.1f;
    static float imm_camera_movement = 0.1f;
    static float yaw = -90.f;
    static float pitch = 0;

    {
        ImGui::Begin("Camera Motion");
        ImGui::SliderFloat("mouse sensitivity", &imm_mouse_sensitivity, 0.1f, 0.9f);
        ImGui::SliderFloat("key sensitivity", &imm_camera_movement, 0.1f, 2.f);
        ImGui::End();
    }

    if (input.keyboard.keydown(SDLK_w))
    {
        camera.position += camera.d * imm_camera_movement;
    }
    if(input.keyboard.keydown(SDLK_s))
    {
        camera.position += camera.d * (-imm_camera_movement);
    }
    if(input.keyboard.keydown(SDLK_a))
    {
        camera.position += glm::normalize(glm::cross(camera.d, camera.up)) * imm_camera_movement;
    }
    if(input.keyboard.keydown(SDLK_d))
    {
        camera.position += glm::normalize(glm::cross(camera.d, camera.up)) * (-imm_camera_movement);
    }

    if(input.keyboard.keydown(SDLK_LSHIFT))
    {
        SDL_SetRelativeMouseMode(SDL_TRUE);
        if(input.mouse.mouse_motion)
        {
            float sensitivity = imm_mouse_sensitivity;

            float xoffset = input.mouse.relx * sensitivity;
            float yoffset = input.mouse.rely * sensitivity;

            yaw += xoffset;
            pitch += yoffset;

            if(pitch > 89.0f) pitch = 89.0f;
            else if(pitch < -89.0) pitch = -89.0f;

            glm::vec3 front;

            front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            front.y = -sin(glm::radians(pitch));
            front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

            camera.d = front;
        }
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

    // used for creating a wigit for updating clear color

    Mesh mesh;

    mesh.position.push_back(glm::vec3(0.0f, 0.0f, -10.0f));
    mesh.position.push_back(glm::vec3(1.0f, 0.0f, -10.0f));
    mesh.position.push_back(glm::vec3(0.0f, 1.0f, -10.0f));

    mesh.normal.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
    mesh.normal.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
    mesh.normal.push_back(glm::vec3(0.0f, 0.0f, 1.0f));

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

        processInput(input, camera, simplerenderer);

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