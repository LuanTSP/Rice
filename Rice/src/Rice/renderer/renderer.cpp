#include "renderer.hpp"
#include "Rice/renderer/opengl/glRendererCommand.hpp"
#include <memory>


namespace Rice
{
    Rice::GraphicsBackend Renderer::m_GraphicsBackend = Rice::GraphicsBackend::OpenGL;

    Renderer::Renderer()
    {
        switch (m_GraphicsBackend) {
            case Rice::GraphicsBackend::None:
            {
                m_RendererCommand = nullptr;
            }

            case Rice::GraphicsBackend::OpenGL:
            {
                m_RendererCommand = std::make_shared<RICE_INTERNAL::glRendererCommand>();
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
}
