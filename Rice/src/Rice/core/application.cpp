#include "application.hpp"
#include "log.hpp"

namespace Rice {
    Application::Application()
    {
        Log::Info("Application initialized");
    }

    void Application::Run() 
    {
        Log::Init(); // Global log initialization
        Log::Info("Application initialized");
        while (true)
        {
            
        }
        Log::Info("Application ended");
    }
}