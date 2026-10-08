#include "glTexture2D.hpp"
#include "Rice/core/log.hpp"
#include <glad/glad.h>
#include <stb_image.h>
#include <stdexcept>
#include <string>

namespace RICE_INTERNAL
{
    glTexture2D::glTexture2D(const std::string& path)
    {
        int width = 0;
        int height = 0;
        stbi_set_flip_vertically_on_load(1);
        unsigned char* data = stbi_load(path.c_str(), &width, &height, nullptr, STBI_rgb_alpha);
        if (data == nullptr)
        {
            std::string msg = "Failed to load texture '" + path + "': ";
            msg += stbi_failure_reason();
            Rice::Log::Error(msg);
            throw std::runtime_error(msg);
        }

        glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
        glTextureStorage2D(m_TextureID, 1, GL_RGBA8, width, height);

        glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureSubImage2D(m_TextureID, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    glTexture2D::~glTexture2D()
    {
        glDeleteTextures(1, &m_TextureID);
    }
    
    void glTexture2D::Bind()
    {
        glBindTextureUnit(0, m_TextureID);
    }
}