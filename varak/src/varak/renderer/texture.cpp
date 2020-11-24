#include "vrpch.h"

#include "varak/renderer/texture.h"

#include "varak/renderer/renderer.h"

#include "platform/opengl/opengl_texture.h"

namespace Varak {

    Ref<Texture2D> Texture2D::create(const std::string& filepath)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: //
            return createRef<OpenGLTexture2D>(filepath);
        }

        VR_CORE_ASSERT_MSG(false, "Unknown RendererAPI!");
        return nullptr;
    }

    Ref<Texture2D> Texture2D::create(uint32_t width, uint32_t height)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: //
            return createRef<OpenGLTexture2D>(width, height);
        }

        VR_CORE_ASSERT_MSG(false, "Unknown RendererAPI!");
        return nullptr;
    }

} // namespace Varak
