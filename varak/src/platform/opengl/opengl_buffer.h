#pragma once

#include "varak/renderer/buffer.h"

namespace Varak {

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, size_t size);

        void bind() override;
        void unbind() override;

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

        void bind() override;
        void unbind() override;

        uint32_t getCount() const override { return m_count; }

    private:
        uint32_t m_rendererID;
        uint32_t m_count;
    };

} // namespace Varak