#include "input.hpp"

namespace Rice
{
    bool Input::m_CurrentKeys[SDL_SCANCODE_COUNT]{};
    bool Input::m_PreviousKeys[SDL_SCANCODE_COUNT]{};

    bool Input::m_CurrentMouse[3]{};
    bool Input::m_PreviousMouse[3]{};

    float Input::m_MouseX = 0.0f;
    float Input::m_MouseY = 0.0f;

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

        // Save previous mouse state.
        for (int i = 0; i < 3; ++i)
        {
            m_PreviousMouse[i] = m_CurrentMouse[i];
        }

        // Deltas are accumulated during the frame.
        m_MouseDeltaX = 0.0f;
        m_MouseDeltaY = 0.0f;

        m_MouseScrollX = 0.0f;
        m_MouseScrollY = 0.0f;
    }


    void Input::OnKeyPressed(SDL_Scancode key)
    {
        if (key < 0 || key >= SDL_SCANCODE_COUNT)
            return;

        m_CurrentKeys[key] = true;
    }


    void Input::OnKeyReleased(SDL_Scancode key)
    {
        if (key < 0 || key >= SDL_SCANCODE_COUNT)
            return;

        m_CurrentKeys[key] = false;
    }


    void Input::OnMouseMoved(
        float x,
        float y,
        float deltaX,
        float deltaY
    )
    {
        m_MouseX = x;
        m_MouseY = y;

        // Accumulate all mouse movement during the frame.
        m_MouseDeltaX += deltaX;
        m_MouseDeltaY += deltaY;
    }


    void Input::OnMouseButtonPressed(Uint8 button)
    {
        const int index = mouseIndex(button);

        if (index >= 0)
            m_CurrentMouse[index] = true;
    }


    void Input::OnMouseButtonReleased(Uint8 button)
    {
        const int index = mouseIndex(button);

        if (index >= 0)
            m_CurrentMouse[index] = false;
    }


    void Input::OnMouseWheel(float x, float y)
    {
        // Accumulate all wheel events during the frame.
        m_MouseScrollX += x;
        m_MouseScrollY += y;
    }


    bool Input::IsKeyDown(Key key)
    {
        const SDL_Scancode scancode = toSDL(key);

        return m_CurrentKeys[scancode];
    }


    bool Input::IsKeyPressed(Key key)
    {
        const SDL_Scancode scancode = toSDL(key);

        return
            m_CurrentKeys[scancode] &&
            !m_PreviousKeys[scancode];
    }


    bool Input::IsKeyReleased(Key key)
    {
        const SDL_Scancode scancode = toSDL(key);

        return
            !m_CurrentKeys[scancode] &&
            m_PreviousKeys[scancode];
    }


    bool Input::IsMouseButtonDown(
        MouseButton button
    )
    {
        return m_CurrentMouse[mouseIndex(button)];
    }


    bool Input::IsMouseButtonPressed(
        MouseButton button
    )
    {
        const int index = mouseIndex(button);

        return
            m_CurrentMouse[index] &&
            !m_PreviousMouse[index];
    }


    bool Input::IsMouseButtonReleased(
        MouseButton button
    )
    {
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


    float Input::MouseScrollX()
    {
        return m_MouseScrollX;
    }


    float Input::MouseScrollY()
    {
        return m_MouseScrollY;
    }


    int Input::mouseIndex(MouseButton button)
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

        return -1;
    }


    int Input::mouseIndex(Uint8 button)
    {
        switch (button)
        {
            case SDL_BUTTON_LEFT:
                return 0;

            case SDL_BUTTON_MIDDLE:
                return 1;

            case SDL_BUTTON_RIGHT:
                return 2;
        }

        return -1;
    }


    SDL_Scancode Input::toSDL(Key key)
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

            case Key::Unknown:
            default:
                return SDL_SCANCODE_UNKNOWN;
        }
    }
}