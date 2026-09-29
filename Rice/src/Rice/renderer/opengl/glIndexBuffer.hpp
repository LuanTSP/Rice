#pragma once
#include "Rice/renderer/indexBuffer.hpp"


namespace RICE_INTERNAL
{
    class glIndexBuffer : public Rice::IndexBuffer
    {
        public:
            glIndexBuffer(uint32_t* indices, uint32_t size);
            void Bind() override;
            void Unbind() override;
        
        private:
            unsigned int m_IBO;
            bool m_Created = false;
    };
}