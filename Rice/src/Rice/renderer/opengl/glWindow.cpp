#include "glWindow.hpp"
#include "Rice/core/log.hpp"
#include "Rice/renderer/opengl/glContext.hpp"

#include "SDL3/SDL_video.h"
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <stdexcept>

namespace RICE_INTERNAL
{
    void glWindow::CreateWindow(
        const std::string& title,
        int width,
        int height
    )
    {
        // Set varialbles
        m_Title = title;
        m_Width = width;
        m_Height = height;

        // Try to init SDL3
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
        {
            std::string msg = "Failed to init SDL: ";
            msg += SDL_GetError();
            Rice::Log::Error(msg);
            throw std::runtime_error(msg);
        }

        // Set SDL version
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(
            SDL_GL_CONTEXT_PROFILE_MASK,
            SDL_GL_CONTEXT_PROFILE_CORE
        );
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        // Create SDL window handle
        m_Window = SDL_CreateWindow(
            m_Title.c_str(),
            m_Width,
            m_Height,
            SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
        );

        // Check if window handle creation was ok
        if (!m_Window)
        {
            std::string msg = "Failed to create window: ";
            msg += SDL_GetError();
            Rice::Log::Error(msg);
            throw std::runtime_error(msg);
        }

        m_GLRenderContext = new GLRenderContext(m_Window);

        // Set context as the GLRenderContext
        m_GLRenderContext->Init();

        if (m_GLRenderContext == nullptr)
        {
            std::string msg = "Failed creating OpenGL context: ";
            msg += SDL_GetError();
            Rice::Log::Error(msg);

            SDL_DestroyWindow(m_Window);
            m_Window = nullptr;
            SDL_Quit();

            throw std::runtime_error(msg);
        }

        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        {
            std::string msg = "Failed initializing GLAD: ";
            msg += SDL_GetError();
            Rice::Log::Error(msg);

            delete m_GLRenderContext;
            SDL_DestroyWindow(m_Window);
            SDL_Quit();

            throw std::runtime_error(msg);
        }

        SetVSync(m_Vsync);

        glViewport(0, 0, m_Width, m_Height);
        glEnable(GL_DEPTH_TEST);
    }

    glWindow::~glWindow()
    {   
        SDL_QuitSubSystem(SDL_INIT_VIDEO);
        SDL_QuitSubSystem(SDL_INIT_EVENTS);
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
    };

    int glWindow::GetWidth() const
    {
        return m_Width;
    }

    int glWindow::GetHeight() const
    {
        return m_Height;
    }


    std::string glWindow::GetTitle() const
    {
        return m_Title;
    }

    bool glWindow::IsVSync() const
    {
        return m_Vsync;
    }

    void glWindow::SetTitle(const std::string& title)
    {
        m_Title = title;
    }

    void glWindow::SetVSync(bool enabled)
    {
        m_Vsync = enabled;
        SDL_GL_SetSwapInterval(enabled ? 1 : 0);
    }

    void glWindow::SwapBuffers()
    {
        SDL_GL_SwapWindow(m_Window);
    }
}