#include "opengl_buffer.h"

#include <glad/glad.h>

namespace Varak {

    // -----------------
    // - Vertex Buffer -
    // -----------------

    OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, uint32_t size, bool isStatic)
    {
        glCreateBuffers(1, &m_handle);
        glBindBuffer(GL_ARRAY_BUFFER, m_handle);
        glBufferData(GL_ARRAY_BUFFER, size, data, isStatic ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_handle); //
    }

    void OpenGLVertexBuffer::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_handle); //
    }

    void OpenGLVertexBuffer::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, GL_NONE); //
    }

    void OpenGLVertexBuffer::setSubData(const void* data, uint32_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_handle);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    // ----------------
    // - Index Buffer -
    // ----------------

    OpenGLIndexBuffer::OpenGLIndexBuffer(const uint16_t* indices, uint32_t count) : m_count(count)
    {
        glCreateBuffers(1, &m_handle);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint16_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_handle); //
    }

    void OpenGLIndexBuffer::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle); //
    }

    void OpenGLIndexBuffer::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_NONE); //
    }

} // namespace Varak
