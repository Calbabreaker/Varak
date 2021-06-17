#include "opengl_buffer.h"

#include <glad/glad.h>

namespace Varak {

    // -----------------
    // - Vertex Buffer -
    // -----------------

    OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
    {
        VR_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
    {
        VR_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_rendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        VR_PROFILE_FUNCTION();

        glDeleteBuffers(1, &m_rendererID);
    }

    void OpenGLVertexBuffer::bind() const
    {
        VR_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    }

    void OpenGLVertexBuffer::unbind() const
    {
        VR_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, GL_NONE); //
    }

    void OpenGLVertexBuffer::setData(const void* data, uint32_t size)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    // ----------------
    // - Index Buffer -
    // ----------------

    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* vertices, uint32_t count) : m_count(count)
    {
        VR_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_rendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), vertices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        VR_PROFILE_FUNCTION();

        glDeleteBuffers(1, &m_rendererID);
    }

    void OpenGLIndexBuffer::bind() const
    {
        VR_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
    }

    void OpenGLIndexBuffer::unbind() const
    {
        VR_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_NONE);
    }

} // namespace Varak
