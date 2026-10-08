#include "Rice/renderer/shader.hpp"
#include "Rice/renderer/renderer.hpp"
#include "Rice/renderer/opengl/glShader.hpp"

namespace Rice
{
    Shader* Shader::Create(const std::string& vertSrc, const std::string& fragSrc)
    {
        switch (Rice::Renderer::GetGraphicsBackend()) 
        {
            case GraphicsBackend::None: 
            {
                std::string msg = "No graphics backend found!";
                Rice::Log::Error(msg);
                throw std::runtime_error(msg.c_str());
            }
            
            case GraphicsBackend::OpenGL:
            {
                return new RICE_INTERNAL::GLShader(vertSrc, fragSrc);
            }
        }

        std::string msg = "Invalid graphics backend!";
        Rice::Log::Error(msg);
        throw std::runtime_error(msg.c_str());
        
        return nullptr;
    }
}

