#pragma once
#include "Rice/renderer/indexBuffer.hpp"
#include <cstdint>


namespace RICE_INTERNAL
{
    class glIndexBuffer : public Rice::IndexBuffer
    {
        public:
            glIndexBuffer(uint32_t* indices, uint32_t size);
            void Bind() override;
            void Unbind() override;
            uint32_t GetCount() override;
        
        private:
            unsigned int m_IBO;
            bool m_Created = false;
            uint32_t m_Count = 0;
    };
}