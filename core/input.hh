#ifndef INPUT_HH
#define INPUT_HH

#include <unordered_map>

#include <core/window.hh>

struct InputHandler
{
    std::unordered_map<int, bool> keycur;
    std::unordered_map<int, bool> keyper;

    Window & target_window;

    InputHandler(Window & _window);

    void update();

    bool keypressed(int keyid);
    bool keyreleased(int keyid);

    bool keydown(int keyid);
    bool keyup(int keyid);
};


#endif