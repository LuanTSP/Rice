#pragma once
#include "Rice/renderer/vertexBuffer.hpp"


namespace RICE_INTERNAL
{
    class glVertexBuffer : public VertexBuffer
    {
        public:
            glVertexBuffer(float* vertices, uint32_t size);
            void Bind() override;
            void Unbind() override;
        
        private:
            unsigned int m_VBO;
            bool m_Created = false;
    };
}