#pragma once

#include <SDL3/SDL.h>

namespace Rice
{
    struct QuitEvent
    {
    };

    struct WindowResizedEvent
    {
        int width;
        int height;
    };

    struct WindowMovedEvent
    {
        int x;
        int y;
    };

    struct KeyPressedEvent
    {
        SDL_Scancode key;
        bool repeat;
    };

    struct KeyReleasedEvent
    {
        SDL_Scancode key;
    };

    struct MouseMovedEvent
    {
        float x;
        float y;
        float deltaX;
        float deltaY;
    };

    struct MouseButtonPressedEvent
    {
        Uint8 button;
        float x;
        float y;
    };

    struct MouseButtonReleasedEvent
    {
        Uint8 button;
        float x;
        float y;
    };

    struct MouseWheelEvent
    {
        float x;
        float y;
    };

    struct TextInputEvent
    {
        const char* text;
    };

    struct WindowCloseRequestedEvent
    {
    };
}