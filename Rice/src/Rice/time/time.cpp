#include "time.hpp"

#include <SDL3/SDL_timer.h>

namespace Rice
{
    double Time::m_TimeNow = 0.0f;
    double Time::m_DeltaTime = 0.0f;

    void Time::BeginFrame()
    {
        static Uint64 previous = SDL_GetTicksNS();

        const Uint64 current = SDL_GetTicksNS();

        m_TimeNow =
            static_cast<double>(current) /
            static_cast<double>(SDL_NS_PER_SECOND);

        m_DeltaTime =
            static_cast<double>(current - previous) /
            static_cast<double>(SDL_NS_PER_SECOND);

        previous = current;
    }
}