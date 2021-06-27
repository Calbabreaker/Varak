#pragma once

#include "vertex_array.h"

namespace Varak {

    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
        void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

        void bind() const override;
        void unbind() const override;

        const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const override
        {
            return m_vertexBuffers;
        };

        const std::shared_ptr<IndexBuffer>& getIndexBuffer() const override
        {
            return m_indexBuffer;
        };

    private:
        uint32_t m_rendererID;
        std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
        std::shared_ptr<IndexBuffer> m_indexBuffer;
    };

} // namespace Varak
