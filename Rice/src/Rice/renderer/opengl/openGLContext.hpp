#pragma once

#include "Rice/renderer/renderContext.hpp"
#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>


namespace RICE_INTERNAL
{
    class OpenGLRenderContext : public RenderContext
    {
        public:
            OpenGLRenderContext(SDL_Window* handle);
            ~OpenGLRenderContext();
            void Init() override;
            void SwapBuffers() override;

        private:
            SDL_Window* m_Handle = nullptr;
            SDL_GLContext m_GLContext;
    };
}