#include "platform/opengl/opengl_framebuffer.h"

#include <glad/glad.h>

namespace Varak {

    OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferProperties& props)
        : m_properties(props)
    {
        invalidate();
    }

    OpenGLFrameBuffer::~OpenGLFrameBuffer()
    {
        glDeleteFramebuffers(1, &m_rendererID);
        glDeleteTextures(1, &m_colorAttachment);
        glDeleteTextures(1, &m_depthAttachment);
    }

    void OpenGLFrameBuffer::invalidate()
    {
        if (m_rendererID)
        {
            glDeleteFramebuffers(1, &m_rendererID);
            glDeleteTextures(1, &m_colorAttachment);
            glDeleteTextures(1, &m_depthAttachment);
        }

        glCreateFramebuffers(1, &m_rendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_colorAttachment);
        glBindTexture(GL_TEXTURE_2D, m_colorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_properties.width,
                     m_properties.height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                               GL_TEXTURE_2D, m_colorAttachment, 0);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_depthAttachment);
        glBindTexture(GL_TEXTURE_2D, m_depthAttachment);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8,
                       m_properties.width, m_properties.height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                               GL_TEXTURE_2D, m_depthAttachment, 0);

        VR_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) ==
                           GL_FRAMEBUFFER_COMPLETE,
                       "FrameBuffer is incomplete!");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFrameBuffer::bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_rendererID);
        glViewport(0, 0, m_properties.width, m_properties.height);
    }

    void OpenGLFrameBuffer::unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0); //
    }

    void OpenGLFrameBuffer::resize(uint32_t width, uint32_t height)
    {
        m_properties.width = width;
        m_properties.height = height;

        invalidate();
    }

} // namespace Varak