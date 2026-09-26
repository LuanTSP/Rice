#include "inputManager.hpp"

namespace Rice {

    InputManager::InputManager()
    {
        update();
    }

    void InputManager::update()
    {
        /*
        * Save previous keyboard state.
        */
        for (int i = 0; i < SDL_SCANCODE_COUNT; ++i)
        {
            m_PreviousKeys[i] = m_CurrentKeys[i];
        }

        /*
        * SDL maintains the current keyboard state for us.
        */
        const bool* keyboard =
            SDL_GetKeyboardState(nullptr);

        for (int i = 0; i < SDL_SCANCODE_COUNT; ++i)
        {
            m_CurrentKeys[i] = keyboard[i];
        }

        /*
        * Save previous mouse state.
        */
        for (int i = 0; i < 3; ++i)
        {
            m_PreviousMouse[i] = m_CurrentMouse[i];
        }

        m_PreviousMouseX = m_MouseX;
        m_PreviousMouseY = m_MouseY;

        /*
        * Get current mouse state.
        */
        float x = 0.0f;
        float y = 0.0f;

        const Uint32 buttons =
            SDL_GetMouseState(&x, &y);

        m_MouseX = x;
        m_MouseY = y;

        m_CurrentMouse[0] =
            (buttons & SDL_BUTTON_LMASK) != 0;

        m_CurrentMouse[1] =
            (buttons & SDL_BUTTON_MMASK) != 0;

        m_CurrentMouse[2] =
            (buttons & SDL_BUTTON_RMASK) != 0;

        /*
        * Mouse movement since the previous frame.
        */
        m_MouseDeltaX =
            m_MouseX - m_PreviousMouseX;

        m_MouseDeltaY =
            m_MouseY - m_PreviousMouseY;
    }

    bool InputManager::isKeyDown(Key key) const
    {
        const SDL_Scancode scancode = toSDL(key);

        return m_CurrentKeys[scancode];
    }

    bool InputManager::isKeyPressed(Key key) const
    {
        const SDL_Scancode scancode = toSDL(key);

        return
            m_CurrentKeys[scancode] &&
            !m_PreviousKeys[scancode];
    }

    bool InputManager::isKeyReleased(Key key) const
    {
        const SDL_Scancode scancode = toSDL(key);

        return
            !m_CurrentKeys[scancode] &&
            m_PreviousKeys[scancode];
    }

    bool InputManager::isMouseButtonDown(
        MouseButton button
    ) const
    {
        return m_CurrentMouse[mouseIndex(button)];
    }

    bool InputManager::isMouseButtonPressed(
        MouseButton button
    ) const
    {
        const int index = mouseIndex(button);

        return
            m_CurrentMouse[index] &&
            !m_PreviousMouse[index];
    }

    bool InputManager::isMouseButtonReleased(
        MouseButton button
    ) const
    {
        const int index = mouseIndex(button);

        return
            !m_CurrentMouse[index] &&
            m_PreviousMouse[index];
    }

    float InputManager::mouseX() const
    {
        return m_MouseX;
    }

    float InputManager::mouseY() const
    {
        return m_MouseY;
    }

    float InputManager::mouseDeltaX() const
    {
        return m_MouseDeltaX;
    }

    float InputManager::mouseDeltaY() const
    {
        return m_MouseDeltaY;
    }

    int InputManager::mouseIndex(MouseButton button)
    {
        switch (button)
        {
            case MouseButton::Left:
                return 0;

            case MouseButton::Middle:
                return 1;

            case MouseButton::Right:
                return 2;
        }

        return 0;
    }

    SDL_Scancode InputManager::toSDL(Key key)
    {
        switch (key)
        {
            case Key::A: return SDL_SCANCODE_A;
            case Key::B: return SDL_SCANCODE_B;
            case Key::C: return SDL_SCANCODE_C;
            case Key::D: return SDL_SCANCODE_D;
            case Key::E: return SDL_SCANCODE_E;
            case Key::F: return SDL_SCANCODE_F;
            case Key::G: return SDL_SCANCODE_G;
            case Key::H: return SDL_SCANCODE_H;
            case Key::I: return SDL_SCANCODE_I;
            case Key::J: return SDL_SCANCODE_J;
            case Key::K: return SDL_SCANCODE_K;
            case Key::L: return SDL_SCANCODE_L;
            case Key::M: return SDL_SCANCODE_M;
            case Key::N: return SDL_SCANCODE_N;
            case Key::O: return SDL_SCANCODE_O;
            case Key::P: return SDL_SCANCODE_P;
            case Key::Q: return SDL_SCANCODE_Q;
            case Key::R: return SDL_SCANCODE_R;
            case Key::S: return SDL_SCANCODE_S;
            case Key::T: return SDL_SCANCODE_T;
            case Key::U: return SDL_SCANCODE_U;
            case Key::V: return SDL_SCANCODE_V;
            case Key::W: return SDL_SCANCODE_W;
            case Key::X: return SDL_SCANCODE_X;
            case Key::Y: return SDL_SCANCODE_Y;
            case Key::Z: return SDL_SCANCODE_Z;

            case Key::Escape:
                return SDL_SCANCODE_ESCAPE;

            case Key::Enter:
                return SDL_SCANCODE_RETURN;

            case Key::Space:
                return SDL_SCANCODE_SPACE;

            case Key::Tab:
                return SDL_SCANCODE_TAB;

            case Key::Left:
                return SDL_SCANCODE_LEFT;

            case Key::Right:
                return SDL_SCANCODE_RIGHT;

            case Key::Up:
                return SDL_SCANCODE_UP;

            case Key::Down:
                return SDL_SCANCODE_DOWN;

            case Key::Shift:
                return SDL_SCANCODE_LSHIFT;

            case Key::Ctrl:
                return SDL_SCANCODE_LCTRL;

            case Key::Alt:
                return SDL_SCANCODE_LALT;

            default:
                return SDL_SCANCODE_UNKNOWN;
        }
    }

} // namespace Engine