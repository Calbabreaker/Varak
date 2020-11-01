#pragma once

namespace Varak {

    class VertexBuffer
    {
    public:
        static std::shared_ptr<VertexBuffer> create(float* vertices, size_t size);

        virtual ~VertexBuffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;
    };

    class IndexBuffer
    {
    public:
        static std::shared_ptr<IndexBuffer> create(uint32_t* indicies,
                                                   uint32_t count);

        virtual ~IndexBuffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual uint32_t getCount() = 0;
    };

} // namespace Varak