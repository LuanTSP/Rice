#include "application.hpp"
#include "Rice/event/events.hpp"
#include "log.hpp"


namespace Rice {
    Application::Application()
    {
        Log::Init(); // Global log initialization
        Log::Info("Application initialized");

        m_Events.subscribe<QuitEvent>([this](const Rice::QuitEvent)
        {
            Quit();
        });
    }

    void Application::Run() 
    {
        
        Log::Info("Application running...");
        m_IsRunning = true;
        while (m_IsRunning)
        {
            m_Events.poll();
            m_Inputs.update();

            this->m_Events.emit(Rice::QuitEvent());
        }
        Log::Info("Application ended");
    }

    void Application::Quit()
    {
        m_IsRunning = false;
    }
}