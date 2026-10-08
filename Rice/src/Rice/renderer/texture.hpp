#pragma once
#include <string>

namespace Rice
{
    class Texture
    {
        public:
            virtual ~Texture() = default;
            virtual void Bind() = 0;
    };

    class Texture2D : public Texture
    {
        public:
            ~Texture2D() override = default;
            void Bind() override = 0;
            static Texture2D* Create(const std::string& path);
    };
}