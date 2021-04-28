#ifndef CORE_WINDOW_HH
#define CORE_WINDOW_HH

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include <functional>

#include <string>

struct Window
{
    SDL_Window * sdl_win = nullptr;
    SDL_GLContext context = nullptr;
    glm::vec3 clear_color;

    std::function<void(void)> callback_close;
    std::function<void(int, int)> callback_resize;

    int width = 0;
    int height = 0;

    bool closed = false;

    Window(std::string window, int width, int height, glm::vec3 _clear_color = glm::vec3(0.0f, 0.0f, 0.0f));
    void clear();
    void update();

    bool is_open();
};

#endif