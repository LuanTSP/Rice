#pragma once

#include "Rice/renderer/rendererCommand.hpp"
#include "Rice/renderer/shader.hpp"
#include "Rice/renderer/vertexArray.hpp"
#include "Rice/renderer/orthoCamera.hpp"
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
            static void Init(const Rice::GraphicsBackend backend);

            static void BeginScene(const std::shared_ptr<OrthoCamera>& camera);
            static void EndScene();
            static void Submit(
                const std::shared_ptr<Rice::VertexArray>& vertexArray,
                const std::shared_ptr<Rice::Shader>& shader
            );
            static void SetClearColor(const glm::vec4& color);
            static void Clear();
            
            static GraphicsBackend GetGraphicsBackend();

        private:
            static GraphicsBackend m_GraphicsBackend;
            static std::shared_ptr<RendererCommand> m_RendererCommand;
            static std::shared_ptr<OrthoCamera> m_OrthoCamera;
    };
}