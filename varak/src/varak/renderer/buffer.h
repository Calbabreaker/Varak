#pragma once

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
        std::string name;
        bool normalized;
        uint32_t size;
        size_t offset;

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
            : type(type), name(name), normalized(normalized), size(shaderTypeSize(type)), offset(0)
        {
        }

        uint32_t getComponentCount() const;
    };

    class BufferLayout
    {
    public:
        BufferLayout() {}
        BufferLayout(std::initializer_list<BufferElement> elements) : m_elements(elements)
        {
            calculateOffsetsAndStride();
        }

        uint32_t getStride() const { return m_stride; }
        const std::vector<BufferElement>& getElements() const { return m_elements; }

        std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_elements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

    private:
        void calculateOffsetsAndStride();

    private:
        std::vector<BufferElement> m_elements;
        uint32_t m_stride = 0;
    };

    class VertexBuffer
    {
    public:
        static Ref<VertexBuffer> create(float* vertices, uint32_t size);
        static Ref<VertexBuffer> create(uint32_t size);

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
        static Ref<IndexBuffer> create(uint32_t* indicies, uint32_t count);

        virtual ~IndexBuffer() = default;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual uint32_t getCount() const = 0;
    };

} // namespace Varak
