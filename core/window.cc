#include "window.hh"

#include <GL/glew.h>
#include <iostream>

Window::Window(std::string _windowname, int _width, int _height, glm::vec3 _clear_color): width(_width), height(_height),clear_color(_clear_color)
{
    sdl_win = SDL_CreateWindow(_windowname.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    if(sdl_win == nullptr)
    {
        std::cerr << "SDL Error (failed creating window): " << SDL_GetError() << std::endl;
        return;
    }

    context = SDL_GL_CreateContext(sdl_win);
    if(context == nullptr)
    {
        std::cerr << "SDL Error (failed creating window opengl context): " << SDL_GetError() << std::endl;
        return;
    }

    GLenum status = glewInit();
    if(status != GLEW_OK)
    {
        std::cerr << "Opengl Error (failde initialising glew): " << glGetError() << std::endl;
        return;
    }

    callback_close = [] () -> void {};
    callback_resize = [=](int _width, int _height) mutable -> void {this->width= _width; this->height= _height;};

    glClearColor(clear_color.r, clear_color.g, clear_color.b, 1.0f);
    glClearDepth(1.0f); // Used for stensil buffer and depth rendering
}

void Window::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::update()
{
    SDL_GL_SwapWindow(sdl_win);
}

bool Window::is_open()
{
    return !closed;
}
