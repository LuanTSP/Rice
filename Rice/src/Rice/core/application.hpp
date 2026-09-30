#pragma once

#include "Rice/input/inputManager.hpp"
#include "Rice/event/eventManager.hpp"
#include "Rice/renderer/vertexArray.hpp"
#include "Rice/renderer/window.hpp"

#include "Rice/renderer/indexBuffer.hpp"
#include "Rice/renderer/opengl/glShader.hpp"
#include "Rice/renderer/vertexBuffer.hpp"

#include <cstdint>
#include <memory>
#include <vector>

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

            struct RenderObject
            {
                std::shared_ptr<RICE_INTERNAL::GLShader> shader;
                std::shared_ptr<VertexBuffer> vertexBuffer;
                std::shared_ptr<IndexBuffer> indexBuffer;
                std::shared_ptr<VertexArray> vertexArray;
                std::uint32_t indexCount = 0;
            };

            std::vector<RenderObject> m_RenderObjects;

            // Private variables
            bool m_IsRunning = false;

            // Private functions
            void Quit();
    };

}