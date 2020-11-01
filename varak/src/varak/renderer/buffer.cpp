#include "varak/renderer/buffer.h"

#include "varak/renderer/renderer.h"

#include "platform/opengl/opengl_buffer.h"

namespace Varak {

    std::shared_ptr<VertexBuffer> VertexBuffer::create(float* vertices,
                                                       size_t size)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::OpenGL:
            return std::make_shared<OpenGLVertexBuffer>(vertices, size);
        }

        VR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

    std::shared_ptr<IndexBuffer> IndexBuffer::create(uint32_t* indicies,
                                                     uint32_t count)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::OpenGL:
            return std::make_shared<OpenGLIndexBuffer>(indicies, count);
        }

        VR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

} // namespace Varak