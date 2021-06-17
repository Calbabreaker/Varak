#include "buffer.h"
#include "renderer.h"

#include "opengl/opengl_buffer.h"

namespace Varak {

    Ref<VertexBuffer> VertexBuffer::create(float* vertices, uint32_t size)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: //
            return createRef<OpenGLVertexBuffer>(vertices, size);
        }

        VR_CORE_ASSERT_MSG(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<VertexBuffer> VertexBuffer::create(uint32_t size)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: //
            return createRef<OpenGLVertexBuffer>(size);
        }

        VR_CORE_ASSERT_MSG(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<IndexBuffer> IndexBuffer::create(uint32_t* indicies, uint32_t count)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: //
            return createRef<OpenGLIndexBuffer>(indicies, count);
        }

        VR_CORE_ASSERT_MSG(false, "Unknown RendererAPI!");
        return nullptr;
    }

    uint32_t shaderTypeSize(ShaderDataType type)
    {
        switch (type)
        {
        case ShaderDataType::Float1: return 4;
        case ShaderDataType::Float2: return 4 * 2;
        case ShaderDataType::Float3: return 4 * 3;
        case ShaderDataType::Float4: return 4 * 4;
        case ShaderDataType::Mat3: return 4 * 3 * 3;
        case ShaderDataType::Mat4: return 4 * 4 * 4;
        case ShaderDataType::Int1: return 4;
        case ShaderDataType::Int2: return 4 * 2;
        case ShaderDataType::Int3: return 4 * 3;
        case ShaderDataType::Int4: return 4 * 4;
        case ShaderDataType::Bool: return 1;
        }

        VR_CORE_ASSERT_MSG(false, "Unknown shader type!");
        return 0;
    }

    void BufferLayout::calculateOffsetsAndStride()
    {
        m_stride = 0;
        for (auto& element : m_elements)
        {
            element.offset = m_stride;
            m_stride += element.size;
        }
    }

    uint32_t BufferElement::getComponentCount() const
    {
        switch (type)
        {
        case ShaderDataType::Float1: return 1;
        case ShaderDataType::Float2: return 2;
        case ShaderDataType::Float3: return 3;
        case ShaderDataType::Float4: return 4;
        case ShaderDataType::Mat3: return 3;
        case ShaderDataType::Mat4: return 4;
        case ShaderDataType::Int1: return 1;
        case ShaderDataType::Int2: return 2;
        case ShaderDataType::Int3: return 3;
        case ShaderDataType::Int4: return 4;
        case ShaderDataType::Bool: return 1;
        }

        VR_CORE_ASSERT_MSG(false, "Unknown shader type!");
        return 0;
    }

} // namespace Varak
