#pragma once
#include "Rice/renderer/bufferLayout.hpp"
#include <cstdint>


namespace Rice
{
    class VertexBuffer
    {
        public:
        static VertexBuffer* Create(float* vertices, uint32_t size);
            virtual ~VertexBuffer() {};
            virtual void Bind() = 0;
            virtual void Unbind() = 0;
            virtual const BufferLayout GetLayout() const = 0;
            virtual void SetLayout(const BufferLayout& layout) = 0;
    };
}