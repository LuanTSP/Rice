#pragma once
#include <cstdint>
#include <stdexcept>
#include <string>
#include <tuple>
#include "Rice/core/log.hpp"


namespace Rice
{
    enum class ShaderDataType
    {
        Float = 0, Float2, Float3, Float4,
        Int, Int2, Int3, Int4,
        Mat2, Mat3, Mat4,
        Bool
    };

    enum class ShaderDataCategory
    {
        Float,
        Integer,
        Boolean
    };

    struct ShaderDataTypeInfo
    {
        uint32_t sizeBytes;
        uint32_t componentCount;
        uint32_t attributeCount;
        ShaderDataCategory category;
    };

    inline ShaderDataTypeInfo GetShaderDataTypeInfo(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float: return {sizeof(float), 1, 1, ShaderDataCategory::Float};
            case ShaderDataType::Float2: return {sizeof(float) * 2, 2, 1, ShaderDataCategory::Float};
            case ShaderDataType::Float3: return {sizeof(float) * 3, 3, 1, ShaderDataCategory::Float};
            case ShaderDataType::Float4: return {sizeof(float) * 4, 4, 1, ShaderDataCategory::Float};

            case ShaderDataType::Int: return {sizeof(uint32_t), 1, 1, ShaderDataCategory::Integer};
            case ShaderDataType::Int2: return {sizeof(uint32_t) * 2, 2, 1, ShaderDataCategory::Integer};
            case ShaderDataType::Int3: return {sizeof(uint32_t) * 3, 3, 1, ShaderDataCategory::Integer};
            case ShaderDataType::Int4: return {sizeof(uint32_t) * 4, 4, 1, ShaderDataCategory::Integer};

            case ShaderDataType::Mat2: return {sizeof(float) * 4, 2, 2, ShaderDataCategory::Float};
            case ShaderDataType::Mat3: return {sizeof(float) * 9, 3, 3, ShaderDataCategory::Float};
            case ShaderDataType::Mat4: return {sizeof(float) * 16, 4, 4, ShaderDataCategory::Float};

            case ShaderDataType::Bool: return {sizeof(bool), 1, 1, ShaderDataCategory::Boolean};
        }

        std::string msg = "Invalid ShaderDataType";
        Rice::Log::Error(msg);
        throw std::runtime_error(msg);
    }

    class VertexBuffer
    {
        public:
        static VertexBuffer* Create(
            float* vertices, 
            uint32_t size, 
            const std::initializer_list<std::tuple<ShaderDataType, std::string>>& layout);
            virtual ~VertexBuffer() {};
            virtual void Bind() = 0;
            virtual void Unbind() = 0;
    };
}