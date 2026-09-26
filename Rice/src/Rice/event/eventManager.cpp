#include "eventManager.hpp"
#include "events.hpp"

namespace Rice {

    void EventManager::poll()
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            processSDLEvent(event);
        }
    }

    void EventManager::processSDLEvent(
        const SDL_Event& event
    )
    {
        switch (event.type)
        {
            case SDL_EVENT_QUIT:
            {
                emit(QuitEvent{});
                break;
            }

            case SDL_EVENT_WINDOW_RESIZED:
            {
                emit(WindowResizedEvent{
                    .width = event.window.data1,
                    .height = event.window.data2
                });

                break;
            }

            case SDL_EVENT_WINDOW_MOVED:
            {
                emit(WindowMovedEvent{
                    .x = event.window.data1,
                    .y = event.window.data2
                });

                break;
            }

            default:
                break;
        }
    }

} // namespace Engine