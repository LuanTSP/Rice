#include "Rice/renderer/renderer.hpp"
#include "vertexBuffer.hpp"
#include "Rice/renderer/opengl/glVertexBuffer.hpp"
#include "Rice/core/log.hpp"

#include <string>
#include <stdexcept>


namespace Rice
{
    // Selects the correct vertex buffer based on the rendering platform
    // For now returns glVertexBuffer*
    // @param vertices  : float*    (pointer to vertex float array)
    // @param size      : uint32_t  (size of the vertez array in bytes)
    VertexBuffer* VertexBuffer::Create(float *vertices, uint32_t size)
    {
        switch (Renderer::GetGraphicsBackend()) 
        {
            case GraphicsBackend::None: 
            {
                std::string msg = "No graphics backend found!";
                Rice::Log::Error(msg);
                throw std::runtime_error(msg.c_str());
            }
            
            case GraphicsBackend::OpenGL:
            {
                return new RICE_INTERNAL::glVertexBuffer(vertices, size);
            }
        }

        std::string msg = "Invalid graphics backend!";
        Rice::Log::Error(msg);
        throw std::runtime_error(msg.c_str());
        
        return nullptr;
    }
}