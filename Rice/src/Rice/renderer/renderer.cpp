#include "renderer.hpp"
#include "Rice/renderer/opengl/glRendererCommand.hpp"
#include "Rice/renderer/rendererCommand.hpp"
#include <memory>


namespace Rice
{
    Rice::GraphicsBackend Renderer::m_GraphicsBackend = Rice::GraphicsBackend::None;
    std::shared_ptr<RendererCommand> Renderer::m_RendererCommand = nullptr;
    std::shared_ptr<OrthoCamera> Renderer::m_OrthoCamera = nullptr;

    void Renderer::Init(const Rice::GraphicsBackend backend)
    {
        switch (backend) {
            case Rice::GraphicsBackend::None:
            {
                m_RendererCommand = nullptr;
                m_GraphicsBackend = backend;
                m_OrthoCamera = nullptr;
                break;
            }

            case Rice::GraphicsBackend::OpenGL:
            {
                m_RendererCommand = std::make_shared<RICE_INTERNAL::glRendererCommand>();
                m_GraphicsBackend = backend;
                m_OrthoCamera = nullptr;
                break;
            }
        }
    }

    void Renderer::BeginScene(const std::shared_ptr<OrthoCamera>& camera) {
        m_OrthoCamera = camera;
        camera->updateView();
    }

    void Renderer::EndScene() {}

    void Renderer::Submit(
        const std::shared_ptr<Rice::VertexArray> &vertexArray,
        const std::shared_ptr<Rice::Shader> &shader
    ) {
        shader->Bind();
        shader->SetMat4("u_View", m_OrthoCamera->GetView());
        shader->SetMat4("u_Proj", m_OrthoCamera->GetProj());
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
