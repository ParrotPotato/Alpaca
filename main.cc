#include <core/window.hh>
#include <core/input.hh>

#include <graphics/shader.hh>

#include <SDL2/SDL.h>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <iostream>
#include <filesystem>



int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    Window window("Main Window", 800, 600);
    window.set_clear_color(glm::vec3(0.3, 0.5, 0.8));

    InputHandler input(window);
    input.escapequit = true;

    std::cout << "Opengl : " << glGetString(GL_VERSION) << "\n";
    std::cout << "Running: " << std::filesystem::current_path() << "\n";

    ShaderProgram program("shader/simple/shader.vs", "shader/simple/shader.fs");

    while(window.isopen())
    {
        window.clear();
        glUseProgram(program.programid);
        
        input.update();
        
        glUseProgram(0);
        window.update();
    }

    return 0;
}