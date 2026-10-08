#pragma once

#include <SDL3/SDL.h>

namespace Rice {

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
}

namespace Rice {

    class Input
    {
        public:
            static void BeginFrame();

            static bool IsKeyDown(Rice::Key key);
            static bool IsKeyPressed(Rice::Key key);
            static bool IsKeyReleased(Rice::Key key);

            static bool IsMouseButtonDown(Rice::MouseButton button);
            static bool IsMouseButtonPressed(Rice::MouseButton button);
            static bool IsMouseButtonReleased(Rice::MouseButton button);

            static float MouseX();
            static float MouseY();

            static float MouseDeltaX();
            static float MouseDeltaY();

            static float MouseScrollX();
            static float MouseScrollY();

        private:
            static SDL_Scancode toSDL(Rice::Key key);
            static int mouseIndex(Rice::MouseButton button);

            static bool m_CurrentKeys[SDL_SCANCODE_COUNT];
            static bool m_PreviousKeys[SDL_SCANCODE_COUNT];

            static bool m_CurrentMouse[3];
            static bool m_PreviousMouse[3];

            static float m_MouseX;
            static float m_MouseY;

            static float m_PreviousMouseX;
            static float m_PreviousMouseY;

            static float m_MouseDeltaX;
            static float m_MouseDeltaY;

            static float m_MouseScrollX;
            static float m_MouseScrollY;
    };

}