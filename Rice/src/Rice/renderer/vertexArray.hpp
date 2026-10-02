#pragma once

#include <cstdint>
#include <memory>

#include "Rice/renderer/indexBuffer.hpp"
#include "Rice/renderer/vertexBuffer.hpp"

namespace Rice
{
    class VertexArray
    {
        public:
            virtual void Bind() = 0;
            virtual void Unbind() = 0;

            virtual void AddVertexBuffer(const std::shared_ptr<Rice::VertexBuffer>& buffer) = 0;
            virtual void SetIndexBuffer(const std::shared_ptr<Rice::IndexBuffer>& buffer) = 0;

            virtual uint32_t GetElementCount() = 0;

            static VertexArray* Create();
    };
}