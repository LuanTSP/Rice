#pragma once

#include "Rice/renderer/shader.hpp"
#include <GLES2/gl2.h>
#include <string>
#include <unordered_map>

namespace RICE_INTERNAL
{
    class GLShader : public Rice::Shader
    {
        public:
            GLShader(const std::string& vertSrc, const std::string& fragSrc);
            ~GLShader();

            void Bind() override;
            void Unbind() override;
            void SetMat4(const std::string& name, const glm::mat4& matrix) override;
        private:
            void LoadUniformLocations();
        private:
            unsigned int m_ProgramID;
            std::unordered_map<std::string, GLint> m_Locations;
    };
}