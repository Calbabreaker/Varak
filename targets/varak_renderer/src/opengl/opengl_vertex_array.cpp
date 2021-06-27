#include "opengl_vertex_array.h"

#include <glad/glad.h>

namespace Varak {

    static GLenum shaderTypeOpenGL(ShaderDataType type)
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
        default: break;
        }

        VR_CORE_ASSERT_MSG(false, "Unknown shader type!");
        return GL_NONE;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_handle); //
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_handle); //
    }

    void OpenGLVertexArray::addVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
    {
        glBindVertexArray(m_handle);
        VR_CORE_ASSERT_MSG(vertexBuffer->getLayout()->getCount(), "BufferLayout can not be empty!");
        vertexBuffer->bind();
        m_vertexBuffers.push_back(vertexBuffer);

        uint32_t index = 0;
        for (const BufferElement& element : vertexBuffer->getLayout()->getElements())
        {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index, element.getComponentCount(),
                                  shaderTypeOpenGL(element.type), element.normalized,
                                  vertexBuffer->getLayout()->getStride(),
                                  reinterpret_cast<const void*>(element.offset));
            index++;
        }
    }

    void OpenGLVertexArray::setIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_handle);
        indexBuffer->bind();
        m_indexBuffer = indexBuffer;
    }

    void OpenGLVertexArray::bind() const
    {
        glBindVertexArray(m_handle); //
    }

    void OpenGLVertexArray::unbind() const
    {
        glBindVertexArray(GL_NONE); //
    }

} // namespace Varak
