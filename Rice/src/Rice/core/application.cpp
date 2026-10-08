#include "application.hpp"
#include "Rice/event/eventManager.hpp"
#include "Rice/input/input.hpp"
#include "Rice/renderer/opengl/glWindow.hpp"
#include "Rice/event/events.hpp"
#include "Rice/renderer/renderer.hpp"
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

        // 3. Initialize managers
        m_Events = std::make_unique<RICE_INTERNAL::EventManager>();

        // 3.1 Subscribe to Quit event (not a must but is good)
        m_Events->subscribe<QuitEvent>([this](const QuitEvent)
        {
            Quit();
        });
    }

    void Application::Run()
    {
        m_IsRunning = true;
        while (m_IsRunning)
        {
            m_Events->poll();
            Rice::Input::BeginFrame();

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