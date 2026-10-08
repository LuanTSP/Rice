#pragma once

#include "Rice/event/eventManager.hpp"
#include "Rice/renderer/window.hpp"
#include "Rice/scene/scene.hpp"

#include <type_traits>
#include <memory>

namespace Rice
{
    class Application
    {
        public:
            Application(const std::string& title, int width, int height);

            ~Application() = default;

            void Run();

            template<typename T, typename ...Args>
            void SetScene(Args&&... args)
            {
                static_assert(
                    std::is_base_of<Rice::Scene, T>::value,
                    "T must inheric from Rice::Scene base class"
                );

                m_ActiveScene = std::make_unique<T>(
                    std::forward<Args>(args)...
                );

                m_ActiveScene->onLoad();
            }
            
        private:
            // Managers
            std::unique_ptr<RICE_INTERNAL::EventManager> m_Events = nullptr;
            
            // Window (TODO:: Make it a window manager)
            std::unique_ptr<Rice::Window> m_Window = nullptr;

            // Private variables
            bool m_IsRunning = false;

            // Scenes
            std::unique_ptr<Rice::Scene> m_ActiveScene = nullptr;
        private:
            void Quit();
    };

}