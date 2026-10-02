#include "glRendererCommand.hpp"
#include "Rice/renderer/vertexArray.hpp"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <memory>

namespace RICE_INTERNAL {
    void glRendererCommand::Clear()
    {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    }

    void glRendererCommand::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void glRendererCommand::DrawIndexed(const std::shared_ptr<Rice::VertexArray>& vertexArray)
    {
        vertexArray->Bind();
        glDrawElements(GL_TRIANGLES, vertexArray->GetElementCount(), GL_UNSIGNED_INT, nullptr);
    }
}