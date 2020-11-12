#pragma once

#include "varak/renderer/texture.h"

namespace Varak {

    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const std::string& filepath);
        ~OpenGLTexture2D();

        uint32_t getWidth() const override { return m_width; };
        uint32_t getHeight() const override { return m_height; };

        void bind(uint32_t slot = 0) const override;

    private:
        uint32_t m_width, m_height;
        uint32_t m_rendererID;
    };

} // namespace Varak
