#include "texture.hpp"
#include "renderer.hpp"
#include "Rice/renderer/opengl/glTexture2D.hpp"


namespace Rice
{
    Texture2D* Texture2D::Create(const std::string& path)
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
                return new RICE_INTERNAL::glTexture2D(path);
            }
        }

        std::string msg = "Invalid graphics backend!";
        Rice::Log::Error(msg);
        throw std::runtime_error(msg.c_str());
        
        return nullptr;
    }
}