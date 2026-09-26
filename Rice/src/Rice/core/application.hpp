#pragma once

#include "../input/inputManager.hpp"
#include "../event/eventManager.hpp"
#include "../window/window.hpp"

#include <memory>

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
        * @brief Constructs an Application instance with default OpenGL backend
        * @param title: std::string (title of the window)
        * @param width: int (width of the window)
        * @param height: int (height the window)
        * @param backend: std::string ("opengl" | "vulkan")
        */
        Application(const std::string title, int width, int height);

        /**
        * @brief Constructs an Application instance with specified backend
        * @param title: std::string (title of the window)
        * @param width: int (width of the window)
        * @param height: int (height the window)
        * @param backend: std::string ("opengl" | "vulkan")
        */
        Application(const std::string title, int width, int height, const std::string& backend);

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
        std::string m_Backend = "opengl";

        std::unique_ptr<RICE_INTERNAL::Window> m_Window = nullptr;
        
        // Quit the application
        void Quit();
    };

}