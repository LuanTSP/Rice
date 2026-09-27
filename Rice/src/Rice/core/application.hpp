#pragma once

#include "Rice/input/inputManager.hpp"
#include "Rice/event/eventManager.hpp"
#include "Rice/renderer/window.hpp"

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
            
        private:
            std::unique_ptr<RICE_INTERNAL::EventManager> m_Events = nullptr;
            std::unique_ptr<RICE_INTERNAL::InputManager> m_Inputs = nullptr;
            std::unique_ptr<RICE_INTERNAL::Window> m_Window = nullptr;
            
            /**
            * @brief Indicates whether the application is currently running.
            */
            bool m_IsRunning = false;
            std::string m_Backend = "opengl";

            
            // Quit the application
            void Quit();
    };

}