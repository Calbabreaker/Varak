#pragma once

#include "varak/renderer/buffer.h"

namespace Varak {

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, size_t size);

        void bind() override;
        void unbind() override;

    private:
        uint32_t m_rendererID;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* vertices, uint32_t count);

        void bind() override;
        void unbind() override;

        uint32_t getCount() override { return m_count; }

    private:
        uint32_t m_rendererID;
        uint32_t m_count;
    };

} // namespace Varak