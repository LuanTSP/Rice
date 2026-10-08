#include "event.hpp"
#include "events.hpp"
#include "Rice/input/input.hpp"


namespace Rice
{
    void Event::BeginFrame()
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            ProcessSDLEvent(event);
        }
    }

    void Event::ProcessSDLEvent(
        const SDL_Event& event
    )
    {
        switch (event.type)
        {
            case SDL_EVENT_QUIT:
            {
                Emit(Rice::QuitEvent{});
                break;
            }

            case SDL_EVENT_WINDOW_RESIZED:
            {
                Emit(
                    Rice::WindowResizedEvent{
                        .width = event.window.data1,
                        .height = event.window.data2
                    }
                );

                break;
            }

            case SDL_EVENT_WINDOW_MOVED:
            {
                Emit(
                    Rice::WindowMovedEvent{
                        .x = event.window.data1,
                        .y = event.window.data2
                    }
                );

                break;
            }

            case SDL_EVENT_KEY_DOWN:
            {
                Rice::Input::OnKeyPressed(
                    event.key.scancode
                );
                
                Emit(
                    Rice::KeyPressedEvent{
                        .key = event.key.scancode,
                        .repeat = event.key.repeat
                    }
                );

                break;
            }

            case SDL_EVENT_KEY_UP:
            {
                Rice::Input::OnKeyReleased(
                    event.key.scancode
                );

                Emit(
                    Rice::KeyReleasedEvent{
                        .key = event.key.scancode
                    }
                );

                break;
            }

            case SDL_EVENT_MOUSE_MOTION:
            {
                Rice::Input::OnMouseMoved(
                    event.motion.x,
                    event.motion.y,
                    event.motion.xrel,
                    event.motion.yrel
                );
                
                Emit(
                    Rice::MouseMovedEvent{
                        .x = event.motion.x,
                        .y = event.motion.y,
                        .deltaX = event.motion.xrel,
                        .deltaY = event.motion.yrel
                    }
                );

                break;
            }

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
            {
                Rice::Input::OnMouseButtonPressed(
                    event.button.button
                );
                
                Emit(
                    Rice::MouseButtonPressedEvent{
                        .button = event.button.button,
                        .x = event.button.x,
                        .y = event.button.y
                    }
                );

                break;
            }

            case SDL_EVENT_MOUSE_BUTTON_UP:
            {
                Rice::Input::OnMouseButtonReleased(
                    event.button.button
                );
                
                Emit(
                    Rice::MouseButtonReleasedEvent{
                        .button = event.button.button,
                        .x = event.button.x,
                        .y = event.button.y
                    }
                );

                break;
            }

            case SDL_EVENT_MOUSE_WHEEL:
            {
                Rice::Input::OnMouseWheel(
                    event.wheel.x,
                    event.wheel.y
                );
                
                Emit(
                    Rice::MouseWheelEvent{
                        .x = event.wheel.x,
                        .y = event.wheel.y
                    }
                );

                break;
            }

            case SDL_EVENT_TEXT_INPUT:
            {
                Emit(
                    Rice::TextInputEvent{
                        .text = event.text.text
                    }
                );

                break;
            }

            default:
                break;
        }
    }
}