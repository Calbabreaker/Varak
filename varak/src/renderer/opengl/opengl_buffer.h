#pragma once

#include "varak/renderer/buffer.h"

namespace Varak {

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(const void* data, uint32_t size, bool isStatic = true);
        ~OpenGLVertexBuffer();

        void bind() const override;
        void unbind() const override;

        void setSubData(const void* data, uint32_t size) override;

    private:
        uint32_t m_handle;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(const uint16_t* indices, uint32_t count);
        ~OpenGLIndexBuffer();

        void bind() const override;
        void unbind() const override;

        uint32_t getCount() const override { return m_count; }

    private:
        uint32_t m_handle;
        uint32_t m_count;
    };

} // namespace Varak
