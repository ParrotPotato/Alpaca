#include <core/input.hh>
#include <core/window.hh>

#include <imgui.h>
#include <imgui_impl_sdl.h>

#include <iostream>

void MouseHandler::swap_buttonbuffer()
{
    for (auto x: mousecur)
    {
        mouseper[x.first] = x.second;
    }

    mouse_pressed = false;
    mouse_motion = false;
    mouse_released = false;
}

bool MouseHandler::buttonclicked(int buttonid)
{
    return mouseper[buttonid] == false && mousecur[buttonid] == true;
}

bool MouseHandler::buttonreleased(int buttonid)
{
    return mouseper[buttonid] == true && mousecur[buttonid] == false;
}

bool MouseHandler::buttondown(int buttonid)
{
    return mousecur[buttonid];
}

bool MouseHandler::buttonup(int buttonid)
{
    return mousecur[buttonid] == false;
}

void MouseHandler::update(SDL_Event & ref_event)
{
    switch(ref_event.type)
    {
        case SDL_MOUSEMOTION:
        {
            relx = ref_event.motion.xrel;
            rely = ref_event.motion.yrel;
            posx = ref_event.motion.x;
            posy = ref_event.motion.y;

            mouse_motion = true;
        }
        break;
        case SDL_MOUSEBUTTONUP:
        {
            mousecur[ref_event.button.button] = false;
            mouse_released = true;
        };
        break;
        case SDL_MOUSEBUTTONDOWN:
        {
            mousecur[ref_event.button.button] = true;
            mouse_pressed = true;
        };
        break;
    }
}

void KeyboardHandler::swap_keybuffer()
{
    for (auto x : keycur)
    {
        keyper[x.first] = x.second;
    }
}

bool KeyboardHandler::keydown(int keyid)
{
    return keycur[keyid];
}

bool KeyboardHandler::keyup(int keyid)
{
    return !keycur[keyid];
}

bool KeyboardHandler::keypressed(int keyid)
{
    return keycur[keyid] == true && keyper[keyid] == false;
}

bool KeyboardHandler::keyreleased(int keyid)
{
    return keycur[keyid] == false && keyper[keyid] == true;
}

void KeyboardHandler::update(SDL_Event & ref_event)
{
    switch(ref_event.type)
    {
        case SDL_KEYDOWN:
        {
            keycur[ref_event.key.keysym.sym] = true;
        }
        break;
        case SDL_KEYUP:
        {
            keycur[ref_event.key.keysym.sym] = false;
        }
        break;
    }
}

InputHandler::InputHandler(Window & _window):target_window(_window)
{
    // don't know what else to do here
}

void InputHandler::update()
{
    keyboard.swap_keybuffer();
    mouse.swap_buttonbuffer();

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        ImGui_ImplSDL2_ProcessEvent(&event);

        if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
            keyboard.update(event);
        }
        if(event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEMOTION)
        {
            mouse.update(event);
        }

        switch (event.type)
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

            default:
            break;
        }
    }

    if(escapequit && keyboard.keydown(SDLK_ESCAPE))
    {
        target_window.callback_close();
        target_window.closed = true;
    }
}
