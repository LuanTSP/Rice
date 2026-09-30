#pragma once

#include "Rice/input/inputManager.hpp"
#include "Rice/event/eventManager.hpp"
#include "Rice/renderer/vertexArray.hpp"
#include "Rice/renderer/window.hpp"

#include "Rice/renderer/indexBuffer.hpp"
#include "Rice/renderer/opengl/glShader.hpp"
#include "Rice/renderer/vertexBuffer.hpp"

#include <memory>

namespace Rice
{
    class Application
    {
        public:
            Application(const std::string title, int width, int height);

            ~Application() = default;

            void Run();
            
        private:
            // Managers
            std::unique_ptr<RICE_INTERNAL::EventManager> m_Events = nullptr;
            std::unique_ptr<RICE_INTERNAL::InputManager> m_Inputs = nullptr;
            
            // Window (TODO:: Make it a window manager)
            std::unique_ptr<Rice::Window> m_Window = nullptr;

            // TODO: remove from here
            std::shared_ptr<RICE_INTERNAL::GLShader> m_Shader;
            std::shared_ptr<VertexBuffer> m_VertexBuffer;
            std::shared_ptr<IndexBuffer> m_IndexBuffer;
            std::shared_ptr<VertexArray> m_VertexArray;

            // Private variables
            bool m_IsRunning = false;

            // Private functions
            void Quit();
    };

}