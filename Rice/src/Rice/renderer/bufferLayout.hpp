#pragma once

#include "Rice/core/log.hpp"
#include <cstdint>
#include <initializer_list>
#include <stdexcept>
#include <string>
#include <vector>


namespace Rice
{
    enum class ShaderDataType
    {
        Float = 0, Float2, Float3, Float4,
        Int, Int2, Int3, Int4,
        Mat2, Mat3, Mat4,
        Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type) {
            // Float
            case ShaderDataType::Float:     return sizeof(float);
            case ShaderDataType::Float2:    return sizeof(float) * 2;
            case ShaderDataType::Float3:    return sizeof(float) * 3;
            case ShaderDataType::Float4:    return sizeof(float) * 4;

            // Int
            case ShaderDataType::Int:       return sizeof(uint32_t);
            case ShaderDataType::Int2:      return sizeof(uint32_t) * 2;
            case ShaderDataType::Int3:      return sizeof(uint32_t) * 3;
            case ShaderDataType::Int4:      return sizeof(uint32_t) * 4;

            // Mat
            case ShaderDataType::Mat2:      return sizeof(float) * 2 * 2;
            case ShaderDataType::Mat3:      return sizeof(float) * 3 * 3;
            case ShaderDataType::Mat4:      return sizeof(float) * 4 * 4;

            // Bool
            case ShaderDataType::Bool:      return sizeof(bool);      
        }

        std::string msg = "Invalid ShaderDataType";
        Rice::Log::Error(msg);
        throw std::runtime_error(msg);
    };
    
    struct BufferElement {
        std::string Name;
        uint32_t Size;
        uint32_t Offset;
        ShaderDataType Type;
        bool Normalized;

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
        {}

        uint32_t GetComponentCount() const
        {
            switch (Type) {
                case ShaderDataType::Float: return 1;
                case ShaderDataType::Float2: return 2;
                case ShaderDataType::Float3: return 3;
                case ShaderDataType::Float4: return 4;

                case ShaderDataType::Int: return 1;
                case ShaderDataType::Int2: return 2;
                case ShaderDataType::Int3: return 3;
                case ShaderDataType::Int4: return 4;

                case ShaderDataType::Mat2: return 2 * 2;
                case ShaderDataType::Mat3: return 3 * 3;
                case ShaderDataType::Mat4: return 4 * 4;

                case ShaderDataType::Bool: return 1;
            }

            std::string msg = "Invalid ShaderDataType";
            Rice::Log::Error(msg);
            throw std::runtime_error(msg);
        }
    };

    class BufferLayout
    {
        public:
            BufferLayout() {};

            BufferLayout(std::initializer_list<BufferElement> elements)
                : m_BufferElements(elements)
            {
                uint32_t offset = 0;
                m_Stride = 0;

                for (auto& e : m_BufferElements)
                {
                    e.Offset = offset;
                    offset += e.Size;
                    m_Stride += e.Size;
                }
            }

            inline const std::vector<BufferElement>& GetBufferElements() const
            {
                return m_BufferElements;
            }

            inline uint32_t GetStride() const
            {
                return m_Stride;
            }

            std::vector<BufferElement>::iterator begin() { return m_BufferElements.begin(); };
            std::vector<BufferElement>::iterator end() { return m_BufferElements.end(); };

            std::vector<BufferElement>::const_iterator begin() const { return m_BufferElements.begin(); };
            std::vector<BufferElement>::const_iterator end() const { return m_BufferElements.end(); };


        private:
            std::vector<BufferElement> m_BufferElements;
            uint32_t m_Stride = 0;
    };
}