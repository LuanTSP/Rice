#pragma once

#include <string>

namespace RICE_INTERNAL
{
    class GLShader
    {
        public:
            GLShader(const std::string& vertSrc, const std::string& fragSrc);
            ~GLShader();

            void Bind();
            void Unbind();
        private:
            unsigned int m_ProgramID;
    };
}