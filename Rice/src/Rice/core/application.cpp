#include "application.hpp"
#include "Rice/event/eventManager.hpp"
#include "Rice/input/inputManager.hpp"
#include "Rice/renderer/opengl/glWindow.hpp"
#include "Rice/event/events.hpp"
#include "log.hpp"

#include <memory>
#include <stdexcept>

namespace Rice {
    Application::Application(const std::string title, int width, int height)
    {
        // Global log initialization
        Log::Init();
        
        // Define rendering backend
        if (m_Backend == "opengl")
        {
            m_Window = std::make_unique<RICE_INTERNAL::glWindow>();
        }
        // else if (backend == "vulkan")
        // {
        //     m_Window = std::make_unique<RICE_INTERNAL::VkWindow>();
        // }

        // Try to create window with selected backend
        if (!m_Window)
        {
            Rice::Log::Error("Unknown backend");
            throw std::invalid_argument("Unknown backend");
        }
        m_Window->CreateWindow(title, width, height);
        
        // Initialization of managers
        m_Events = std::make_unique<RICE_INTERNAL::EventManager>();
        m_Inputs = std::make_unique<RICE_INTERNAL::InputManager>();

        // Subscrive to Quit event for window to be able to close (default choice)
        m_Events->subscribe<QuitEvent>([this](const QuitEvent)
        {
            Quit();
        });

        Log::Info("Application initialized");
    }

    Application::Application(const std::string title, int width, int height, const std::string& backend)
    {
        // 1. Global log initialization
        Log::Init();
        
        // 2. Define backend
        m_Backend = backend;
        
        // 3. Define rendering backend
        if (m_Backend == "opengl")
        {
            m_Window = std::make_unique<RICE_INTERNAL::glWindow>();
        }
        // else if (backend == "vulkan")
        // {
        //     m_Window = std::make_unique<RICE_INTERNAL::VkWindow>();
        // }

        // 4. Try to create window with selected backend
        if (!m_Window)
        {
            Rice::Log::Error("Unknown backend");
            throw std::invalid_argument("Unknown backend");
        }
        m_Window->CreateWindow(title, width, height);
        
        // 5. Initialization of managers
        m_Events = std::make_unique<RICE_INTERNAL::EventManager>();
        m_Inputs = std::make_unique<RICE_INTERNAL::InputManager>();

        // 6. Subscrive to Quit event for window to be able to close (default choice)
        m_Events->subscribe<QuitEvent>([this](const QuitEvent)
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
            m_Events->poll();
            m_Inputs->update();
        }
        
        Log::Info("Application ended.");
    }

    void Application::Quit()
    {
        m_IsRunning = false;
    }
}