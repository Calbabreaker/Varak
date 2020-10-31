#include "varak/renderer/rendering_context.h"

#include "varak/renderer/renderer.h"

#include "platform/opengl/opengl_rendering_context.h"

namespace Varak {

    std::unique_ptr<RenderingContext> RenderingContext::create(void* window)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::OpenGL:
            return std::make_unique<OpenGLRenderingContext>(
                reinterpret_cast<GLFWwindow*>(window));
        }

        VR_CORE_ASSERT(false, "Unknown RendererAPI");
    }

} // namespace Varak