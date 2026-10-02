#pragma once

#include "Rice/renderer/vertexArray.hpp"
#include <memory>
#include <glm/glm.hpp>

namespace Rice
{
    class RendererCommand
    {
        public:
            virtual void SetClearColor(const glm::vec4& color) = 0;
            virtual void Clear() = 0;
            virtual void DrawIndexed(const std::shared_ptr<Rice::VertexArray>& vertexArray) = 0;
            virtual ~RendererCommand() = default;
    };
}