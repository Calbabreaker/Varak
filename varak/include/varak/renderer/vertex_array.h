#pragma once

#include "varak/renderer/buffer.h"

namespace Varak {

    class VertexArray
    {
    public:
        static std::shared_ptr<VertexArray> create();

        virtual ~VertexArray() = default;

        virtual void addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
        virtual void setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

        virtual void bind() const = 0;
        virtual void unbind() const = 0;

        virtual const std::vector<std::shared_ptr<VertexBuffer>>& getVertexBuffers() const = 0;
        virtual const std::shared_ptr<IndexBuffer>& getIndexBuffer() const = 0;
    };

} // namespace Varak
