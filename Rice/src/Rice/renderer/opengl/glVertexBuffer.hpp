#pragma once
#include "Rice/renderer/bufferLayout.hpp"
#include "Rice/renderer/vertexBuffer.hpp"


namespace RICE_INTERNAL
{
    class glVertexBuffer : public Rice::VertexBuffer
    {
        public:
            glVertexBuffer(float* vertices, uint32_t size);
            void Bind() override;
            void Unbind() override;
            void SetLayout(const Rice::BufferLayout& layout) override { m_Layout = layout; };
            const Rice::BufferLayout GetLayout() const override { return m_Layout; };
        
        private:
            unsigned int m_VBO;
            bool m_Created = false;
            Rice::BufferLayout m_Layout;
    };
}