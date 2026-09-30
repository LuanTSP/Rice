#include "vertexArray.hpp"
#include "Rice/renderer/renderer.hpp"
#include "Rice/renderer/opengl/glVertexArray.hpp"

namespace Rice
{
    VertexArray* VertexArray::Create()
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
                return new RICE_INTERNAL::glVertexArray();
            }
        }

        std::string msg = "Invalid graphics backend!";
        Rice::Log::Error(msg);
        throw std::runtime_error(msg.c_str());
        
        return nullptr;
    }
}