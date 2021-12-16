#include "opengl_texture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Varak {

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, int channels)
    {
        GLenum internalFormat = GL_NONE, dataFormat = GL_NONE;
        if (channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        createTexture();
    }

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
        : m_width(width), m_height(height)
    {
        m_internalFormat = GL_RGBA8;
        m_dataFormat = GL_RGBA;
        createTexture();
    }

    void OpenGLTexture2D::createTexture()
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);
        glTextureStorage2D(m_handle, 1, m_internalFormat, int(m_width), int(m_height));

        glTextureParameteri(m_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(m_handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_handle, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_handle); //
    }

    void OpenGLTexture2D::setData(const void* data)
    {
        glTextureSubImage2D(m_handle, 0, 0, 0, int(m_width), int(m_height), m_dataFormat,
                            GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture2D::bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, m_handle); //
    }

} // namespace Varak
