#pragma once

#include "varak/renderer/texture.h"

#include <glad/glad.h>

namespace Varak {

    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string& filepath);
        OpenGLTexture2D(uint32_t width, uint32_t height);
        ~OpenGLTexture2D();

        uint32_t getWidth() const override { return m_width; };
        uint32_t getHeight() const override { return m_height; };
        uint32_t getHandle() const override { return m_handle; };

        void setData(void* data, uint32_t size) override;

        void bind(uint32_t slot = 0) const override;

        bool operator==(const Texture& other) const override
        {
            return m_handle == reinterpret_cast<const OpenGLTexture2D&>(other).m_handle;
        }

    private:
        uint32_t m_width, m_height;
        uint32_t m_handle;
        GLenum m_internalFormat, m_dataFormat;
    };

} // namespace Varak
