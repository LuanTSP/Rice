#include "openGLContext.hpp"

namespace RICE_INTERNAL
{
    OpenGLRenderContext::OpenGLRenderContext(SDL_Window* handle)
        : m_Handle(handle)
    {}

    OpenGLRenderContext::~OpenGLRenderContext()
    {
        SDL_GL_DestroyContext(m_GLContext);
    }

    void OpenGLRenderContext::Init()
    {
        m_GLContext = SDL_GL_CreateContext(m_Handle);
    }

    void OpenGLRenderContext::SwapBuffers()
    {
        
    }
}