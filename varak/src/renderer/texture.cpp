#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_SIMD
#include <stb_image.h>

#include "varak/renderer/renderer.h"
#include "varak/renderer/texture.h"

#include "opengl/opengl_texture.h"

namespace Varak {

    std::shared_ptr<Texture2D> Texture2D::create(const std::string& filepath)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: //
            return std::make_shared<OpenGLTexture2D>(filepath);
        }

        VR_CORE_ASSERT_MSG(false, "Unknown RendererAPI!");
        return nullptr;
    }

    std::shared_ptr<Texture2D> Texture2D::create(uint32_t width, uint32_t height)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: //
            return std::make_shared<OpenGLTexture2D>(width, height);
        }

        VR_CORE_ASSERT_MSG(false, "Unknown RendererAPI!");
        return nullptr;
    }

} // namespace Varak
