#pragma once

#include "varak/renderer/vertex_array.h"

namespace Varak {

    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        void addVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
        void setIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

        void bind() const override;
        void unbind() const override;

        const std::vector<Ref<VertexBuffer>>& getVertexBuffers() const override
        {
            return m_vertexBuffers;
        };
        const Ref<IndexBuffer>& getIndexBuffer() const override
        {
            return m_indexBuffer;
        };

    private:
        uint32_t m_rendererID;
        std::vector<Ref<VertexBuffer>> m_vertexBuffers;
        Ref<IndexBuffer> m_indexBuffer;
    };

} // namespace Varak
