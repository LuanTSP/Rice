#include "glVertexArray.hpp"
#include <memory>
#include <glad/glad.h>

namespace RICE_INTERNAL
{
    static GLenum ShaderDataTypeToOpenGLBaseType(Rice::ShaderDataType type)
    {
        switch (type) {
            case Rice::ShaderDataType::Float:
            case Rice::ShaderDataType::Float2:
            case Rice::ShaderDataType::Float3:
            case Rice::ShaderDataType::Float4:
            case Rice::ShaderDataType::Mat2:
            case Rice::ShaderDataType::Mat3:
            case Rice::ShaderDataType::Mat4:
                return GL_FLOAT;

            case Rice::ShaderDataType::Int:
            case Rice::ShaderDataType::Int2:
            case Rice::ShaderDataType::Int3:
            case Rice::ShaderDataType::Int4:
                return GL_INT;

            case Rice::ShaderDataType::Bool:
                return GL_BOOL;
        }

        std::string msg = "Invalid ShaderDataType";
        Rice::Log::Error(msg);
        throw std::runtime_error(msg);
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
        glBindVertexArray(m_ID);
        buffer->Bind();

        const auto& layout = buffer->GetLayout();
        uint32_t index = 0;
        for (auto& e : layout)
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, 
                e.GetComponentCount(), 
                ShaderDataTypeToOpenGLBaseType(e.Type), 
                e.Normalized ? GL_TRUE : GL_FALSE , 
                layout.GetStride(), 
                reinterpret_cast<const void*>(static_cast<std::uintptr_t>(e.Offset)));
            index++;
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