#include "input.hpp"
#include "SDL3/SDL_mouse.h"

namespace Rice {

    bool Input::m_CurrentKeys[SDL_SCANCODE_COUNT]{};
    bool Input::m_PreviousKeys[SDL_SCANCODE_COUNT]{};

    bool Input::m_CurrentMouse[3]{};
    bool Input::m_PreviousMouse[3]{};

    float Input::m_MouseX = 0.0f;
    float Input::m_MouseY = 0.0f;

    float Input::m_PreviousMouseX = 0.0f;
    float Input::m_PreviousMouseY = 0.0f;

    float Input::m_MouseDeltaX = 0.0f;
    float Input::m_MouseDeltaY = 0.0f;

    float Input::m_MouseScrollX = 0.0f;
    float Input::m_MouseScrollY = 0.0f;

    void Input::BeginFrame()
    {
        // Save previous keyboard state.
        for (int i = 0; i < SDL_SCANCODE_COUNT; ++i)
        {
            m_PreviousKeys[i] = m_CurrentKeys[i];
        }

        // SDL maintains the current keyboard state for us.
        const bool* keyboard =
            SDL_GetKeyboardState(nullptr);

        for (int i = 0; i < SDL_SCANCODE_COUNT; ++i)
        {
            m_CurrentKeys[i] = keyboard[i];
        }

        // Save previous mouse state.
        for (int i = 0; i < 3; ++i)
        {
            m_PreviousMouse[i] = m_CurrentMouse[i];
        }

        m_PreviousMouseX = m_MouseX;
        m_PreviousMouseY = m_MouseY;

        // Get current mouse state.
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

        
        // Mouse movement since the previous frame.
        m_MouseDeltaX =
            m_MouseX - m_PreviousMouseX;

        m_MouseDeltaY =
            m_MouseY - m_PreviousMouseY;
        
        // Reset mouse scroll
        m_MouseScrollX = 0.0f;
        m_MouseScrollY = 0.0f;
    }

    bool Input::IsKeyDown(Rice::Key key)
    {
        const SDL_Scancode scancode = toSDL(key);

        return m_CurrentKeys[scancode];
    }

    bool Input::IsKeyPressed(Rice::Key key)
    {
        const SDL_Scancode scancode = toSDL(key);

        return
            m_CurrentKeys[scancode] &&
            !m_PreviousKeys[scancode];
    }

    bool Input::IsKeyReleased(Rice::Key key)
    {
        const SDL_Scancode scancode = toSDL(key);

        return
            !m_CurrentKeys[scancode] &&
            m_PreviousKeys[scancode];
    }

    bool Input::IsMouseButtonDown(
        Rice::MouseButton button
    )
    {
        return m_CurrentMouse[mouseIndex(button)];
    }

    bool Input::IsMouseButtonPressed(
        Rice::MouseButton button
    ) {
        const int index = mouseIndex(button);

        return
            m_CurrentMouse[index] &&
            !m_PreviousMouse[index];
    }

    bool Input::IsMouseButtonReleased(
        Rice::MouseButton button
    ) {
        const int index = mouseIndex(button);

        return
            !m_CurrentMouse[index] &&
            m_PreviousMouse[index];
    }

    float Input::MouseX()
    {
        return m_MouseX;
    }

    float Input::MouseY()
    {
        return m_MouseY;
    }

    float Input::MouseDeltaX()
    {
        return m_MouseDeltaX;
    }

    float Input::MouseDeltaY()
    {
        return m_MouseDeltaY;
    }

    int Input::mouseIndex(Rice::MouseButton button)
    {
        switch (button)
        {
            case Rice::MouseButton::Left:
                return 0;

            case Rice::MouseButton::Middle:
                return 1;

            case Rice::MouseButton::Right:
                return 2;
        }

        return 0;
    }

    float Input::MouseScrollX()
    {
        return m_MouseScrollX;
    }

    float Input::MouseScrollY()
    {
        return m_MouseScrollY;
    }

    SDL_Scancode Input::toSDL(Rice::Key key)
    {
        switch (key)
        {
            case Rice::Key::A: return SDL_SCANCODE_A;
            case Rice::Key::B: return SDL_SCANCODE_B;
            case Rice::Key::C: return SDL_SCANCODE_C;
            case Rice::Key::D: return SDL_SCANCODE_D;
            case Rice::Key::E: return SDL_SCANCODE_E;
            case Rice::Key::F: return SDL_SCANCODE_F;
            case Rice::Key::G: return SDL_SCANCODE_G;
            case Rice::Key::H: return SDL_SCANCODE_H;
            case Rice::Key::I: return SDL_SCANCODE_I;
            case Rice::Key::J: return SDL_SCANCODE_J;
            case Rice::Key::K: return SDL_SCANCODE_K;
            case Rice::Key::L: return SDL_SCANCODE_L;
            case Rice::Key::M: return SDL_SCANCODE_M;
            case Rice::Key::N: return SDL_SCANCODE_N;
            case Rice::Key::O: return SDL_SCANCODE_O;
            case Rice::Key::P: return SDL_SCANCODE_P;
            case Rice::Key::Q: return SDL_SCANCODE_Q;
            case Rice::Key::R: return SDL_SCANCODE_R;
            case Rice::Key::S: return SDL_SCANCODE_S;
            case Rice::Key::T: return SDL_SCANCODE_T;
            case Rice::Key::U: return SDL_SCANCODE_U;
            case Rice::Key::V: return SDL_SCANCODE_V;
            case Rice::Key::W: return SDL_SCANCODE_W;
            case Rice::Key::X: return SDL_SCANCODE_X;
            case Rice::Key::Y: return SDL_SCANCODE_Y;
            case Rice::Key::Z: return SDL_SCANCODE_Z;

            case Rice::Key::Escape:
                return SDL_SCANCODE_ESCAPE;

            case Rice::Key::Enter:
                return SDL_SCANCODE_RETURN;

            case Rice::Key::Space:
                return SDL_SCANCODE_SPACE;

            case Rice::Key::Tab:
                return SDL_SCANCODE_TAB;

            case Rice::Key::Left:
                return SDL_SCANCODE_LEFT;

            case Rice::Key::Right:
                return SDL_SCANCODE_RIGHT;

            case Rice::Key::Up:
                return SDL_SCANCODE_UP;

            case Rice::Key::Down:
                return SDL_SCANCODE_DOWN;

            case Rice::Key::Shift:
                return SDL_SCANCODE_LSHIFT;

            case Rice::Key::Ctrl:
                return SDL_SCANCODE_LCTRL;

            case Rice::Key::Alt:
                return SDL_SCANCODE_LALT;

            default:
                return SDL_SCANCODE_UNKNOWN;
        }
    }

}