#include "window.hh"

#include <GL/glew.h>
#include <iostream>

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>



Window::Window(std::string windowname, int _width, int _height, glm::vec4 _clear_color, float _clear_depth, bool _imgui_enabled): width(_width), height(_height), clear_color(_clear_color), clear_depth(_clear_depth), imgui_enabled(_imgui_enabled)
{
    sdl_win = SDL_CreateWindow(windowname.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
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

    glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
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

bool Window::isopen()
{
    return !closed;
}

void Window::set_clear_color(glm::vec4 _clear_color)
{
    glClearColor(_clear_color.r, _clear_color.g, _clear_color.b, _clear_color.a);
    clear_color = _clear_color;
}

void Window::set_clear_depth(float _clear_depth)
{
    glClearDepth(_clear_depth);
    clear_depth = _clear_depth;
}

Window::~Window()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(sdl_win);
}