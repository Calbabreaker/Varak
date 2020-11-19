#pragma once

#include "varak/renderer/buffer.h"

namespace Varak {

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        OpenGLVertexBuffer(uint32_t size);
        ~OpenGLVertexBuffer();

        void bind() const override;
        void unbind() const override;

        void setData(const void* data, uint32_t size) override;

        const BufferLayout& getLayout() const override { return m_layout; }
        void setLayout(const BufferLayout& layout) override
        {
            m_layout = layout;
        }

    private:
        uint32_t m_rendererID;
        BufferLayout m_layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* vertices, uint32_t count);
        ~OpenGLIndexBuffer();

        void bind() const override;
        void unbind() const override;

        uint32_t getCount() const override { return m_count; }

    private:
        uint32_t m_rendererID;
        uint32_t m_count;
    };

} // namespace Varak
