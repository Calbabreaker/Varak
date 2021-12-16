#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_SIMD
#include <stb_image.h>

#include "varak/renderer/renderer.h"
#include "varak/renderer/texture.h"

#include "opengl/opengl_texture.h"

namespace Varak {

    std::shared_ptr<Texture2D> Texture2D::create(const std::string& filepath)
    {

        // load texture
        int width, height, channels;
        stbi_uc* data = nullptr;
        stbi_set_flip_vertically_on_load(1);
        data = stbi_load(filepath.c_str(), &width, &height, &channels, 4);
        VR_CORE_ASSERT_MSG(data, "Failed to load image at {}!", filepath);

        std::shared_ptr<OpenGLTexture2D> texture;
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL:
            texture =
                std::make_shared<OpenGLTexture2D>(uint32_t(width), uint32_t(height), channels);

        default: VR_CORE_ASSERT_MSG(false, "Texture2D unimplemented for api!"); return nullptr;
        }

        texture->setData(data);
        stbi_image_free(data);
    }

    std::shared_ptr<Texture2D> Texture2D::create(uint32_t width, uint32_t height)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: //
            return std::make_shared<OpenGLTexture2D>(width, height);

        default: VR_CORE_ASSERT_MSG(false, "Texture2D unimplemented for api!"); return nullptr;
        }
    }

} // namespace Varak
