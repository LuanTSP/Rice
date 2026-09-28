#include "glContext.hpp"

namespace RICE_INTERNAL
{
    GLRenderContext::GLRenderContext(SDL_Window* handle)
        : m_Handle(handle)
    {}

    GLRenderContext::~GLRenderContext()
    {
        SDL_GL_DestroyContext(m_GLContext);
    }

    void GLRenderContext::Init()
    {
        m_GLContext = SDL_GL_CreateContext(m_Handle);
    }
}