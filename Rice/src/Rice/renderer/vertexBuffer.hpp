#pragma once
#include <cstdint>


namespace RICE_INTERNAL
{
    class VertexBuffer
    {
        public:
            virtual void Bind() = 0;
            virtual void Unbind() = 0;
            static VertexBuffer* Create(float* vertices, uint32_t size);
    };
}