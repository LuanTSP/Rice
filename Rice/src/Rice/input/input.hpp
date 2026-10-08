#pragma once

#include <SDL3/SDL.h>

namespace Rice
{
    class Event;
}

namespace Rice
{
    enum class Key
    {
        Unknown,

        A, B, C, D, E, F, G, H, I, J, K, L, M,
        N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

        Escape,
        Enter,
        Space,
        Tab,

        Left,
        Right,
        Up,
        Down,

        Shift,
        Ctrl,
        Alt
    };

    enum class MouseButton
    {
        Left,
        Middle,
        Right
    };

    class Input
    {
    public:
        static void BeginFrame();

        static bool IsKeyDown(Key key);
        static bool IsKeyPressed(Key key);
        static bool IsKeyReleased(Key key);

        static bool IsMouseButtonDown(MouseButton button);
        static bool IsMouseButtonPressed(MouseButton button);
        static bool IsMouseButtonReleased(MouseButton button);

        static float MouseX();
        static float MouseY();

        static float MouseDeltaX();
        static float MouseDeltaY();

        static float MouseScrollX();
        static float MouseScrollY();

    private:
        friend class Rice::Event;

        static void OnKeyPressed(
            SDL_Scancode key
        );

        static void OnKeyReleased(
            SDL_Scancode key
        );

        static void OnMouseMoved(
            float x,
            float y,
            float deltaX,
            float deltaY
        );

        static void OnMouseButtonPressed(
            Uint8 button
        );

        static void OnMouseButtonReleased(
            Uint8 button
        );

        static void OnMouseWheel(
            float x,
            float y
        );

        static SDL_Scancode toSDL(Key key);

        static int mouseIndex(
            MouseButton button
        );

        static int mouseIndex(
            Uint8 button
        );

        static bool m_CurrentKeys[SDL_SCANCODE_COUNT];
        static bool m_PreviousKeys[SDL_SCANCODE_COUNT];

        static bool m_CurrentMouse[3];
        static bool m_PreviousMouse[3];

        static float m_MouseX;
        static float m_MouseY;

        static float m_MouseDeltaX;
        static float m_MouseDeltaY;

        static float m_MouseScrollX;
        static float m_MouseScrollY;
    };
}