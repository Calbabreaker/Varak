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

    uint32_t shaderTypeSize(ShaderDataType type);

    struct BufferElement
    {
        ShaderDataType type;
        const char* name;
        bool normalized;
        uint32_t size;
        uint32_t offset;

        BufferElement(ShaderDataType p_type, const char* p_name, bool p_normalized = false)
            : type(p_type), name(p_name), normalized(p_normalized), size(shaderTypeSize(p_type)),
              offset(0)
        {
        }

        uint32_t getComponentCount() const;
    };

    class BufferLayout
    {
    public:
        BufferLayout(std::initializer_list<BufferElement> elements);

        uint32_t getStride() const { return m_stride; }
        size_t getCount() const { return m_elements.size(); }
        const std::vector<BufferElement>& getElements() const { return m_elements; }

    private:
        std::vector<BufferElement> m_elements;
        uint32_t m_stride = 0;
    };

    class VertexBuffer
    {
    public:
        static std::shared_ptr<VertexBuffer> create(const void* data, uint32_t size,
                                                    bool isStatic = true);
        virtual ~VertexBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual void setSubData(const void* data, uint32_t size) = 0;

        virtual const std::shared_ptr<BufferLayout>& getLayout() const = 0;
        virtual void setLayout(const std::shared_ptr<BufferLayout>& layout) = 0;
    };

    class IndexBuffer
    {
    public:
        static std::shared_ptr<IndexBuffer> create(const uint16_t* indices, uint32_t count);
        virtual ~IndexBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual uint32_t getCount() const = 0;
    };

} // namespace Varak
