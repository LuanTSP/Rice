#pragma once

#include "Rice/renderer/indexBuffer.hpp"
#include "Rice/renderer/vertexBuffer.hpp"
#include "Rice/renderer/vertexArray.hpp"
#include <cstdint>

namespace RICE_INTERNAL
{
    class glVertexArray : public Rice::VertexArray
    {
        public:
            glVertexArray();
            ~glVertexArray();
            
            void Bind() override;
            void Unbind() override;

            void AddVertexBuffer(const std::shared_ptr<Rice::VertexBuffer>& buffer) override;
            virtual void SetIndexBuffer(const std::shared_ptr<Rice::IndexBuffer>& buffer) override;

            uint32_t GetElementCount() override;
        
        private:
            std::vector<std::shared_ptr<Rice::VertexBuffer>> m_VertexBuffers;
            std::shared_ptr<Rice::IndexBuffer> m_IndexBuffer;
            uint32_t m_ID;
    };
}