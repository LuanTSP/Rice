#include "application.hpp"
#include "../window/glWindow.hpp"
#include "Rice/event/events.hpp"
#include "log.hpp"

#include <stdexcept>

namespace Rice {
    Application::Application(const std::string title, int width, int height)
    {
        Log::Init(); // Global log initialization
        
        if (m_Backend == "opengl")
        {
            m_Window = std::make_unique<RICE_INTERNAL::glWindow>();
        }    

        // else if (backend == "vulkan")
        // {
        //     m_Window = std::make_unique<RICE_INTERNAL::VkWindow>();
        // }

        if (!m_Window)
        {
            Rice::Log::Error("Unknown backend");
            throw std::invalid_argument("Unknown backend");
        }

        m_Window->CreateWindow(title, width, height);
        
        m_Events.subscribe<QuitEvent>([this](const Rice::QuitEvent)
        {
            Quit();
        });

        Log::Info("Application initialized");
    }

    Application::Application(const std::string title, int width, int height, const std::string& backend)
    {
        m_Backend = backend;
        Log::Init(); // Global log initialization
        
        if (m_Backend == "opengl")
        {
            m_Window = std::make_unique<RICE_INTERNAL::glWindow>();
        }    

        // else if (backend == "vulkan")
        // {
        //     m_Window = std::make_unique<RICE_INTERNAL::VkWindow>();
        // }

        if (!m_Window)
        {
            Rice::Log::Error("Unknown backend");
            throw std::invalid_argument("Unknown backend");
        }

        m_Window->CreateWindow(title, width, height);
        
        m_Events.subscribe<QuitEvent>([this](const Rice::QuitEvent)
        {
            Quit();
        });

        Log::Info("Application initialized");
    }

    void Application::Run()
    {
        Log::Info("Application running...");
        
        m_IsRunning = true;
        while (m_IsRunning)
        {
            m_Events.poll();
            m_Inputs.update();
        }
        
        Log::Info("Application ended.");
    }

    void Application::Quit()
    {
        m_IsRunning = false;
    }
}