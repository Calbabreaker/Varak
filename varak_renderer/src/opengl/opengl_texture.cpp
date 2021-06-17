#include "opengl_texture.h"

#include <glad/glad.h>
#include <stb_image.h>

namespace Varak {

    OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath)
    {
        VR_PROFILE_FUNCTION();

        stbi_set_flip_vertically_on_load(1);

        int width, height, channels;
        stbi_uc* data = nullptr;
        {
            VR_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D");
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

        VR_CORE_ASSERT_MSG(internalFormat & dataFormat, "Format not supported with image at {0}!", filepath);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
        glTextureStorage2D(m_rendererID, 1, internalFormat, m_width, m_height);

        glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) : m_width(width), m_height(height)
    {
        VR_PROFILE_FUNCTION();

        m_internalFormat = GL_RGBA8;
        m_dataFormat = GL_RGBA;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_rendererID);
        glTextureStorage2D(m_rendererID, 1, m_internalFormat, m_width, m_height);

        glTextureParameteri(m_rendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_rendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_rendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        VR_PROFILE_FUNCTION();

        glDeleteTextures(1, &m_rendererID); //
    }

    void OpenGLTexture2D::setData(void* data, uint32_t size)
    {
        VR_PROFILE_FUNCTION();

        uint32_t bpp = m_dataFormat == GL_RGBA ? 4 : 3;
        VR_CORE_ASSERT_MSG(size == m_width * m_height * bpp, "Data must be entire texture!");
        glTextureSubImage2D(m_rendererID, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
    }

    void OpenGLTexture2D::bind(uint32_t slot) const
    {
        VR_PROFILE_FUNCTION();

        glBindTextureUnit(slot, m_rendererID);
    }

} // namespace Varak
