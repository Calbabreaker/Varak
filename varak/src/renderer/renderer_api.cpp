#include "varak/renderer/renderer.h"

#include "opengl/opengl_renderer_api.h"

namespace Varak {

    std::unique_ptr<RendererAPI> RendererAPI::create()
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: //
            return std::make_unique<OpenGLRendererAPI>();

        default: VR_CORE_ASSERT_MSG(false, "RendererAPI unimplemented for api!"); return nullptr;
        }
    }

} // namespace Varak
