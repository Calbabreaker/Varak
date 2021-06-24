#include "rendering_context.h"
#include "renderer.h"

#include "opengl/opengl_context.h"

namespace Varak {

    Scope<RenderingContext> RenderingContext::create(void* window)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: //
            return createScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
        }

        VR_CORE_ASSERT_MSG(false, "Unknown RendererAPI!");
        return nullptr;
    }

} // namespace Varak
