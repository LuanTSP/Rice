#pragma once

#include "Rice/renderer/rendererCommand.hpp"
#include "Rice/renderer/vertexArray.hpp"
#include <memory>


namespace Rice
{
    enum class GraphicsBackend
    {
        None = 0,
        OpenGL = 1,
        // Vulkan = 2,
        // DX11 = 3,
        // DX12 = 4,
        // Metal = 5,
    };

    class Renderer
    {
        public:
            Renderer();

            void BeginScene();
            void EndScene();
            void Submit(const std::shared_ptr<Rice::VertexArray>& vertexArray);
            void SetClearColor(const glm::vec4& color);
            void Clear();
            
            static GraphicsBackend GetGraphicsBackend() { return m_GraphicsBackend; }

        private:
            static GraphicsBackend m_GraphicsBackend;
            std::shared_ptr<RendererCommand> m_RendererCommand;
    };
}