#pragma once

#include "../input/inputManager.hpp"
#include "../event/eventManager.hpp"

namespace Rice
{

    /**
    * @brief Main entry point of the Rice engine.
    *
    * The Application class manages the engine's main execution loop
    * and provides the entry point for running the application.
    */
    class Application
    {
    public:

        /**
        * @brief Constructs an Application instance.
        */
        Application();

        /**
        * @brief Destroys the Application instance.
        */
        ~Application() = default;

        /**
        * @brief Starts the application's main loop.
        */
        void Run();
        EventManager m_Events;
        InputManager m_Inputs;

    private:
        
        /**
        * @brief Indicates whether the application is currently running.
        */
        bool m_IsRunning = false;
        
        // Quit the application
        void Quit();
    };

}