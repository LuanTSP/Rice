#pragma once
#include "Rice/renderer/texture.hpp"
#include <cstdint>

namespace RICE_INTERNAL
{
    class glTexture2D : public Rice::Texture2D
    {
        public:
            glTexture2D(const std::string& path);
            ~glTexture2D();

            void Bind() override;

        private:
            uint32_t m_TextureID;
    };
}