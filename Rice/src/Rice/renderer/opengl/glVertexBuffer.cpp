#include "glVertexBuffer.hpp"
#include "Rice/core/log.hpp"
#include <cstdint>
#include <glad/glad.h>

namespace RICE_INTERNAL
{
    glVertexBuffer::glVertexBuffer(float* vertices, uint32_t size)
    {
        // Generate buffer
        glGenBuffers(1, &m_VBO);
        // Bind it
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        // Pass data
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
        // Layout TODO: REMOVE LAYOUT FROM HERE
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  3 * sizeof(float), nullptr);
        // Unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        m_Created = true;
    }

    void glVertexBuffer::Bind()
    {
        if (m_Created == true)
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            return;
        
        Rice::Log::Error("Tried to bind an non created glVertexBuffer");
    }

    void glVertexBuffer::Unbind()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}