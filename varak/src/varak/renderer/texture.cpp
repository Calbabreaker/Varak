#include "varak/renderer/texture.h"

#include "varak/renderer/renderer.h"

#include "platform/opengl/opengl_texture.h"

namespace Varak {

    Ref<Texture2D> Texture2D::create(const std::string& filepath)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL:
            return createRef<OpenGLTexture2D>(filepath);
        }

        VR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

} // namespace Varak
