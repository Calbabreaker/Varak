#include "varak/renderer/buffer.h"
#include "varak/renderer/renderer.h"

#include "opengl/opengl_buffer.h"

namespace Varak {

    std::shared_ptr<VertexBuffer> VertexBuffer::create(const void* data, uint32_t size,
                                                       bool isStatic)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: //
            return std::make_shared<OpenGLVertexBuffer>(data, size, isStatic);

        default: VR_CORE_ASSERT_MSG(false, "VertexBuffer unimplemented for api!"); return nullptr;
        }
    }

    std::shared_ptr<IndexBuffer> IndexBuffer::create(const uint16_t* indicies, uint32_t count)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: //
            return std::make_shared<OpenGLIndexBuffer>(indicies, count);

        default: VR_CORE_ASSERT_MSG(false, "IndexBuffer unimplemented for api!"); return nullptr;
        }
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
        default: break;
        }

        VR_CORE_ASSERT_MSG(false, "Unknown shader type!");
        return 0;
    }

    BufferLayout::BufferLayout(std::initializer_list<BufferElement> elements) : m_elements(elements)
    {
        m_stride = 0;
        for (BufferElement& element : m_elements)
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
        default: break;
        }

        VR_CORE_ASSERT_MSG(false, "Unknown shader type!");
        return 0;
    }

} // namespace Varak
