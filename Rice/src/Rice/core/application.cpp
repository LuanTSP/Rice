#include "application.hpp"
#include "Rice/input/input.hpp"
#include "Rice/renderer/opengl/glWindow.hpp"
#include "Rice/event/events.hpp"
#include "Rice/event/event.hpp"
#include "Rice/renderer/renderer.hpp"
#include "Rice/time/time.hpp"
#include "log.hpp"

#include <memory>

namespace Rice 
{
    Application::Application(const std::string& title, int width, int height)
    {
        // 1. Initialize logging
        Log::Init();
        Renderer::Init(Rice::GraphicsBackend::OpenGL);

        // 2. Initialize window with OpenGL backend TODO: switch the backend implementation automatically
        m_Window = std::make_unique<RICE_INTERNAL::glWindow>();

        if (!m_Window)
        {
            Rice::Log::Error("Unknown backend");
            throw std::invalid_argument("Unknown backend");
        }

        m_Window->CreateWindow(title, width, height);

        // 3 Subscribe to Quit event (not a must but is good)
        Rice::Event::Subscribe<QuitEvent>([this](const QuitEvent)
        {
            Quit();
            Rice::Log::Info("Quit event");
        });
    }

    void Application::Run()
    {
        m_IsRunning = true;
        while (m_IsRunning)
        {
            Rice::Time::BeginFrame();
            Rice::Input::BeginFrame();
            Rice::Event::BeginFrame();

            if (m_ActiveScene)
            {
                m_ActiveScene->onUpdate();
            }

            m_Window->SwapBuffers();
        }
    }

    void Application::Quit()
    {
        m_IsRunning = false;
    }
}