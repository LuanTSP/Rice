#pragma once

#include <cstdint>
#include <string>

namespace RICE_INTERNAL
{
    class OpenGLShader
    {
        public:
            OpenGLShader(const std::string& vertSrc, const std::string& fragSrc);
            ~OpenGLShader();

            void Bind();
            void Unbind();
        private:
            unsigned int m_ProgramID;
    };
}