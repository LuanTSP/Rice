#pragma once
#include "Rice/renderer/vertexBuffer.hpp"
#include <cstdint>
#include <initializer_list>
#include <vector>

namespace RICE_INTERNAL
{
    class glVertexBuffer : public Rice::VertexBuffer
    {
        public:
            glVertexBuffer(float* vertices, uint32_t size, const std::initializer_list<std::tuple<Rice::ShaderDataType, std::string>>& layout);
            void Bind() override;
            void Unbind() override;

            std::vector<Rice::ShaderDataType>& GetShaderDataTypes() { return m_ShaderDataTypes; }
            std::vector<std::string>& GetShaderVarNames() { return m_ShaderVarNames; }
            std::vector<uint32_t>& GetOffsets() { return m_Offsets; }
            uint32_t GetStride() { return m_Stride; }
        
        private:
            unsigned int m_VBO;
            bool m_Created = false;
            std::vector<Rice::ShaderDataType> m_ShaderDataTypes;
            std::vector<std::string> m_ShaderVarNames;
            std::vector<uint32_t> m_Offsets;
            uint32_t m_Stride = 0;
    };
}