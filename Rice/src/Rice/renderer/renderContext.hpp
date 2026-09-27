#pragma once

namespace RICE_INTERNAL
{
    class RenderContext
    {
        public:
            virtual void Init() = 0;
            virtual void SwapBuffers() = 0;
    };
}