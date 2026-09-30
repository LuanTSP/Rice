#include "glIndexBuffer.hpp"
#include "Rice/core/log.hpp"
#include <cstdint>
#include <glad/glad.h>

namespace RICE_INTERNAL
{
    glIndexBuffer::glIndexBuffer(uint32_t* indices, uint32_t size)
    {
        // Generate buffer
        glGenBuffers(1, &m_IBO);
        // Bind it
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
        // Pass data
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
        // Unbind
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        m_Created = true;
    }

    void glIndexBuffer::Bind()
    {
        if (m_Created == true)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
            return;
        }

        Rice::Log::Error("Tried to bind an non created glIndexBuffer");
    }

    void glIndexBuffer::Unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}