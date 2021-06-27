#include "opengl_texture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Varak {

    OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath)
    {
        stbi_set_flip_vertically_on_load(1);

        int width, height, channels;
        stbi_uc* data = nullptr;
        {
            data = stbi_load(filepath.c_str(), &width, &height, &channels, 4);
        }

        VR_CORE_ASSERT_MSG(data, "Failed to load image at {0}!", filepath);
        m_width = width;
        m_height = height;

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

        VR_CORE_ASSERT_MSG(internalFormat & dataFormat, "Format not supported with image at {0}!",
                           filepath);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);
        glTextureStorage2D(m_handle, 1, internalFormat, m_width, m_height);

        glTextureParameteri(m_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(m_handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_handle, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_handle, 0, 0, 0, m_width, m_height, dataFormat, GL_UNSIGNED_BYTE,
                            data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
        : m_width(width), m_height(height)
    {
        m_internalFormat = GL_RGBA8;
        m_dataFormat = GL_RGBA;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_handle);
        glTextureStorage2D(m_handle, 1, m_internalFormat, m_width, m_height);

        glTextureParameteri(m_handle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_handle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(m_handle, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_handle, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_handle); //
    }

    void OpenGLTexture2D::setData(void* data, uint32_t size)
    {
        uint32_t bpp = m_dataFormat == GL_RGBA ? 4 : 3;
        VR_CORE_ASSERT_MSG(size == m_width * m_height * bpp, "Data must be entire texture!");
        glTextureSubImage2D(m_handle, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE,
                            data);
    }

    void OpenGLTexture2D::bind(uint32_t slot) const { glBindTextureUnit(slot, m_handle); }

} // namespace Varak
