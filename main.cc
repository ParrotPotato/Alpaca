#include <SDL2/SDL.h>
#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <core/window.hh>
#include <core/input.hh>

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    Window window("Main Window", 800, 600);

    InputHandler input(window);

    std::cout << "Opengl : " << glGetString(GL_VERSION) << "\n";

    while(window.is_open())
    {
        input.update();
    }

    return 0;
}