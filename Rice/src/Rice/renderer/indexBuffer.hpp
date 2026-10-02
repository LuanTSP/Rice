#pragma once

#include <cstdint>

namespace Rice
{
    class IndexBuffer
    {
        public:
            static IndexBuffer* Create(uint32_t* indices, uint32_t size);
            virtual void Bind() = 0;
            virtual void Unbind() = 0;
            virtual uint32_t GetCount() = 0;

    };
}