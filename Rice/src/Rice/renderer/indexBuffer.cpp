#include "indexBuffer.hpp"
#include "Rice/core/log.hpp"
#include "Rice/renderer/opengl/glIndexBuffer.hpp"
#include "Rice/renderer/renderer.hpp"

namespace Rice
{
    // Selects the correct Index buffer based on the rendering platform
    // For now returns glIndexBuffer*
    // @param indices   : float*    (pointer to Index float array)
    // @param size      : uint32_t  (size of the vertez array in bytes)
    IndexBuffer* IndexBuffer::Create(uint32_t *indices, uint32_t size)
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
                return new RICE_INTERNAL::glIndexBuffer(indices, size);
            }
        }

        std::string msg = "Invalid graphics backend!";
        Rice::Log::Error(msg);
        throw std::runtime_error(msg.c_str());
        
        return nullptr;
    }
}