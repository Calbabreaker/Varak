#include "varak/renderer/rendering_context.h"

#include "varak/renderer/renderer.h"

#include "platform/opengl/opengl_rendering_context.h"

namespace Varak {

    Scope<RenderingContext> RenderingContext::create(void* window)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL:
            return createScope<OpenGLRenderingContext>(
                static_cast<GLFWwindow*>(window));
        }

        VR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

} // namespace Varak
