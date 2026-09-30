#pragma once

#include <cstdint>

namespace Rice
{
    class IndexBuffer
    {
        public:
            virtual void Bind() = 0;
            virtual void Unbind() = 0;
            static IndexBuffer* Create(uint32_t* indices, uint32_t size);
    };
}