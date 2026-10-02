#pragma once
#include "Rice/renderer/rendererCommand.hpp"


namespace RICE_INTERNAL
{
    class glRendererCommand : public Rice::RendererCommand
    {
        public:
            glRendererCommand() = default;

            void SetClearColor(const glm::vec4& color) override;
            void Clear() override;
            void DrawIndexed(const std::shared_ptr<Rice::VertexArray>& vertexArray) override;   
    };
}