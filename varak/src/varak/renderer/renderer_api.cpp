#include "varak/renderer/renderer.h"

#include "platform/opengl/opengl_renderer_api.h"

namespace Varak {

    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

    Scope<RendererAPI> RendererAPI::create()
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: return createScope<OpenGLRendererAPI>();
        }

        VR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

} // namespace Varak
