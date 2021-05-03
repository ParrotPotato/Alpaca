#ifndef INPUT_HH
#define INPUT_HH

#include <unordered_map>

#include <core/window.hh>

struct MouseHandler
{
    float posx, posy;
    float relx, rely;

    std::unordered_map<int, bool> mousecur;
    std::unordered_map<int, bool> mouseper;

    bool mouse_motion;
    bool mouse_pressed;
    bool mouse_released;

    // TODO(nitesh): Do we really need double click check ? 

    void swap_buttonbuffer();
    void update(SDL_Event & ref_event);

    bool buttondown(int buttonid);
    bool buttonup(int buttonid);

    bool buttonclicked(int buttonid);
    bool buttonreleased(int buttonid);
};

struct KeyboardHandler
{
    std::unordered_map<int, bool> keycur;
    std::unordered_map<int, bool> keyper;

    void swap_keybuffer();
    void update(SDL_Event & ref_event);

    bool keypressed(int keyid);
    bool keyreleased(int keyid);

    bool keydown(int keyid);
    bool keyup(int keyid);
};

struct InputHandler
{
    KeyboardHandler keyboard;
    MouseHandler mouse;

    Window & target_window;

    bool escapequit = false;

    InputHandler(Window & _window);

    void update();
};


#endif