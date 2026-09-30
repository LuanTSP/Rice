#include "glVertexBuffer.hpp"
#include "Rice/core/log.hpp"
#include "Rice/renderer/vertexBuffer.hpp"
#include <glad/glad.h>

namespace RICE_INTERNAL
{
    glVertexBuffer::glVertexBuffer(float* vertices, uint32_t size, const std::initializer_list<std::tuple<Rice::ShaderDataType, std::string>>& layout)
    {
        // 1. Generate buffer and pass data
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // 2. Configure layout
        uint32_t offset = 0;

        for (const auto& [type, name] : layout)
        {
            m_ShaderDataTypes.push_back(type);
            m_ShaderVarNames.push_back(name);
            const uint32_t size = Rice::GetShaderDataTypeInfo(type).sizeBytes;
            m_Offsets.push_back(offset);
            offset += size;
            m_Stride += size;
        }
        
        m_Created = true;
    }

    void glVertexBuffer::Bind()
    {
        if (m_Created == true)
        {
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            return;
        }

        Rice::Log::Error("Tried to bind an non created glVertexBuffer");
    }

    void glVertexBuffer::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}