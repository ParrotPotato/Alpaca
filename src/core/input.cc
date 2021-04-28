#include <core/input.hh>
#include <core/window.hh>

#include <iostream>


InputHandler::InputHandler(Window & _window):target_window(_window)
{
    // don't know what else to do here
}

void InputHandler::update()
{
    // shifting the device state to prev device state
    {
        for(auto x: keycur)
        {
            keyper[x.first] = x.second;
        }
    }

    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
            {
                target_window.callback_close();
                target_window.closed = true;
            }
            break;

            case SDL_WINDOWEVENT_RESIZED:
            {
                target_window.callback_resize(event.window.data1, event.window.data2);
            }
            break;

            case SDL_KEYDOWN:
            {
                keycur[event.key.keysym.sym] = true;
            }
            break;
            case SDL_KEYUP:
            {
                keycur[event.key.keysym.sym] = false;
            }
            break;

            default:
            break;
        }

    }

    if(keypressed(SDLK_ESCAPE) == true)
    {
        target_window.callback_close();
        target_window.closed = true;
    }
}

bool InputHandler::keydown(int keyid)
{
    return keycur[keyid];
}

bool InputHandler::keyup(int keyid)
{
    return !keycur[keyid];
}

bool InputHandler::keypressed(int keyid)
{
    return keycur[keyid] == true && keyper[keyid] == false;
}

bool InputHandler::keyreleased(int keyid)
{
    return keycur[keyid] == false && keyper[keyid] == true;
}