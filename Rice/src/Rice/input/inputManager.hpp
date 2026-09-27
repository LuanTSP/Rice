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

namespace RICE_INTERNAL {

    class InputManager
    {
        public:
            InputManager();
            ~InputManager() = default;

            InputManager(const InputManager&) = delete;
            InputManager& operator=(const InputManager&) = delete;

            /*
            * Update the input state.
            *
            * Must be called once per frame.
            */
            void update();

            bool isKeyDown(Rice::Key key) const;
            bool isKeyPressed(Rice::Key key) const;
            bool isKeyReleased(Rice::Key key) const;

            bool isMouseButtonDown(Rice::MouseButton button) const;
            bool isMouseButtonPressed(Rice::MouseButton button) const;
            bool isMouseButtonReleased(Rice::MouseButton button) const;

            float mouseX() const;
            float mouseY() const;

            float mouseDeltaX() const;
            float mouseDeltaY() const;

        private:
            static SDL_Scancode toSDL(Rice::Key key);
            static int mouseIndex(Rice::MouseButton button);

            bool m_CurrentKeys[SDL_SCANCODE_COUNT]{};
            bool m_PreviousKeys[SDL_SCANCODE_COUNT]{};

            bool m_CurrentMouse[3]{};
            bool m_PreviousMouse[3]{};

            float m_MouseX = 0.0f;
            float m_MouseY = 0.0f;

            float m_PreviousMouseX = 0.0f;
            float m_PreviousMouseY = 0.0f;

            float m_MouseDeltaX = 0.0f;
            float m_MouseDeltaY = 0.0f;
    };

} // namespace Engine