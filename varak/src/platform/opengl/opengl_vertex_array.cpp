#include "platform/opengl/opengl_vertex_array.h"

#include <glad/glad.h>

namespace Varak {

    namespace {

        GLenum shaderTypeOpenGL(ShaderDataType type)
        {
            switch (type)
            {
            case ShaderDataType::Float1: return GL_FLOAT;
            case ShaderDataType::Float2: return GL_FLOAT;
            case ShaderDataType::Float3: return GL_FLOAT;
            case ShaderDataType::Float4: return GL_FLOAT;
            case ShaderDataType::Mat3: return GL_FLOAT;
            case ShaderDataType::Mat4: return GL_FLOAT;
            case ShaderDataType::Int1: return GL_INT;
            case ShaderDataType::Int2: return GL_INT;
            case ShaderDataType::Int3: return GL_INT;
            case ShaderDataType::Int4: return GL_INT;
            case ShaderDataType::Bool: return GL_BOOL;
            }

            VR_CORE_ASSERT(false, "Unknown shader type!");
            return 0;
        }

    } // namespace

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_rendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_rendererID);
    }

    void OpenGLVertexArray::addVertexBuffer(
        const Ref<VertexBuffer>& vertexBuffer)
    {
        glBindVertexArray(m_rendererID);
        VR_CORE_ASSERT(vertexBuffer->getLayout().getElements().size(),
                       "BufferLayout can not be empty!");
        vertexBuffer->bind();
        m_vertexBuffers.push_back(vertexBuffer);

        uint32_t index = 0;
        for (auto& element : vertexBuffer->getLayout())
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(
                index, element.getComponentCount(),
                shaderTypeOpenGL(element.type), element.normalized,
                vertexBuffer->getLayout().getStride(),
                reinterpret_cast<const void*>(element.offset));
            index++;
        }
    }

    void OpenGLVertexArray::setIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_rendererID);
        indexBuffer->bind();
        m_indexBuffer = indexBuffer;
    }

    void OpenGLVertexArray::bind() const
    {
        glBindVertexArray(m_rendererID); //
    }

    void OpenGLVertexArray::unbind() const
    {
        glBindVertexArray(0); //
    }

} // namespace Varak
