#include "renderer.hpp"
#include "Rice/renderer/opengl/glRendererCommand.hpp"
#include "Rice/renderer/rendererCommand.hpp"
#include <memory>


namespace Rice
{
    Rice::GraphicsBackend Renderer::m_GraphicsBackend = Rice::GraphicsBackend::None;
    std::shared_ptr<RendererCommand> Renderer::m_RendererCommand = nullptr;

    void Renderer::Init(const Rice::GraphicsBackend backend)
    {
        switch (backend) {
            case Rice::GraphicsBackend::None:
            {
                m_RendererCommand = nullptr;
                m_GraphicsBackend = backend;
                break;
            }

            case Rice::GraphicsBackend::OpenGL:
            {
                m_RendererCommand = std::make_shared<RICE_INTERNAL::glRendererCommand>();
                m_GraphicsBackend = backend;
                break;
            }
        }
    }

    void Renderer::BeginScene() {}
    void Renderer::EndScene() {}
    void Renderer::Submit(const std::shared_ptr<Rice::VertexArray> &vertexArray)
    {
        m_RendererCommand->DrawIndexed(vertexArray);
    }

    void Renderer::SetClearColor(const glm::vec4& color)
    {
        m_RendererCommand->SetClearColor(color);
    }

    void Renderer::Clear()
    {
        m_RendererCommand->Clear();
    }

    GraphicsBackend Renderer::GetGraphicsBackend() { return m_GraphicsBackend; }
}
