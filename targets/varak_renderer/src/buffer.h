#pragma once

#include "varak_core.h"

#include <string>
#include <vector>

namespace Varak {

    enum class ShaderDataType
    {
        None = 0,
        Float1,
        Float2,
        Float3,
        Float4,
        Mat3,
        Mat4,
        Int1,
        Int2,
        Int3,
        Int4,
        Bool
    };

    int32_t shaderTypeSize(ShaderDataType type);

    struct BufferElement
    {
        ShaderDataType type;
        const char* name;
        bool normalized;
        int32_t size;
        int32_t offset;

        BufferElement(ShaderDataType p_type, const char* p_name, bool p_normalized = false)
            : type(p_type), name(p_name), normalized(p_normalized), size(shaderTypeSize(p_type)),
              offset(0)
        {
        }

        int32_t getComponentCount() const;
    };

    class BufferLayout
    {
    public:
        BufferLayout() = default;
        BufferLayout(std::initializer_list<BufferElement> elements);

        int32_t getStride() const { return m_stride; }
        const std::vector<BufferElement>& getElements() const { return m_elements; }

        std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

    private:
        std::vector<BufferElement> m_elements;
        int32_t m_stride = 0;
    };

    class VertexBuffer
    {
    public:
        static std::shared_ptr<VertexBuffer> create(float* vertices, uint32_t size);
        static std::shared_ptr<VertexBuffer> create(uint32_t size);

        virtual ~VertexBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void setData(const void* data, uint32_t size) = 0;

        virtual const BufferLayout& getLayout() const = 0;
        virtual void setLayout(const BufferLayout& layout) = 0;
    };

    class IndexBuffer
    {
    public:
        static std::shared_ptr<IndexBuffer> create(uint32_t* indicies, uint32_t count);

        virtual ~IndexBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual uint32_t getCount() const = 0;
    };

} // namespace Varak
