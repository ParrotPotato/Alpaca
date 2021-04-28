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
    float clear_depth;

    std::function<void(void)> callback_close;
    std::function<void(int, int)> callback_resize;

    int width = 0;
    int height = 0;

    bool closed = false;

    Window(std::string windowname, int width, int height, glm::vec3 _clear_color = glm::vec3(0.0f, 0.0f, 0.0f), float _clear_depth = 1.0f);

    void set_clear_color(glm::vec3 color);
    void set_clear_depth(float depth);

    void clear();
    void update();

    bool isopen();
};

#endif