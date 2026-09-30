#include "glVertexArray.hpp"
#include "Rice/renderer/opengl/glVertexBuffer.hpp"
#include "Rice/renderer/vertexBuffer.hpp"
#include <glad/glad.h>

namespace RICE_INTERNAL
{
    static GLenum ShaderDataTypeToOpenGLBaseType(Rice::ShaderDataCategory category)
    {
        switch (category) {
            case Rice::ShaderDataCategory::Float:
                return GL_FLOAT;

            case Rice::ShaderDataCategory::Integer:
                return GL_INT;

            case Rice::ShaderDataCategory::Boolean:
                Rice::Log::Error("Boolean vertex attributes are not supported by OpenGL");
                throw std::runtime_error("Boolean vertex attributes are not supported by OpenGL");
        }

        throw std::runtime_error("Invalid ShaderDataCategory");
    }

    glVertexArray::glVertexArray() 
    {
        glGenVertexArrays(1, &m_ID);
        glBindVertexArray(m_ID);
    }

    glVertexArray::~glVertexArray()
    {
        glDeleteVertexArrays(1, &m_ID);
    }
        
    void glVertexArray::Bind() 
    {
        glBindVertexArray(m_ID);
    }

    void glVertexArray::Unbind()
    {
        glBindVertexArray(0);
    }

    void glVertexArray::AddVertexBuffer(const std::shared_ptr<Rice::VertexBuffer>& buffer)
    {
        auto buff = std::dynamic_pointer_cast<glVertexBuffer>(buffer);

        glBindVertexArray(m_ID);
        buffer->Bind();

        uint32_t attributeIndex = 0;
        uint32_t elementIndex = 0;
        for (auto& type : buff->GetShaderDataTypes())
        {
            const Rice::ShaderDataTypeInfo info = Rice::GetShaderDataTypeInfo(type);
            const GLenum baseType = ShaderDataTypeToOpenGLBaseType(info.category);
            const uintptr_t elementOffset = buff->GetOffsets()[elementIndex++];
            const uint32_t columnSize = info.sizeBytes / info.attributeCount;

            for (uint32_t column = 0; column < info.attributeCount; ++column)
            {
                const uint32_t location = attributeIndex + column;
                const uintptr_t offset = elementOffset + column * columnSize;

                glEnableVertexAttribArray(location);
                if (info.category == Rice::ShaderDataCategory::Integer)
                {
                    glVertexAttribIPointer(
                        location,
                        info.componentCount,
                        baseType,
                        buff->GetStride(),
                        reinterpret_cast<const void*>(offset));
                }
                else
                {
                    glVertexAttribPointer(
                        location,
                        info.componentCount,
                        baseType,
                        GL_FALSE,
                        buff->GetStride(),
                        reinterpret_cast<const void*>(offset));
                }
            }

            attributeIndex += info.attributeCount;
        }

        m_VertexBuffers.push_back(buffer);
    }
    void glVertexArray::SetIndexBuffer(const std::shared_ptr<Rice::IndexBuffer>& buffer)
    {
        glBindVertexArray(m_ID);
        buffer->Bind();

        m_IndexBuffer = buffer;
    }
}