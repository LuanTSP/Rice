#pragma once

#include "glm/ext/matrix_float4x4.hpp"

namespace Rice
{
    class Shader
    {
        public:
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void SetMat4(const std::string& name, const glm::mat4& matrix) = 0;
    };
}
