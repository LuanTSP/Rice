#pragma once

#include "Rice/renderer/renderContext.hpp"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>


namespace RICE_INTERNAL
{
    class GLRenderContext : public Rice::RenderContext
    {
        public:
            GLRenderContext(SDL_Window* handle);
            ~GLRenderContext();
            void Init() override;

        private:
            SDL_Window* m_Handle = nullptr;
            SDL_GLContext m_GLContext;
    };
}