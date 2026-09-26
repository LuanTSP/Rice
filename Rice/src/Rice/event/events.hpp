#pragma once

namespace Rice {

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

}