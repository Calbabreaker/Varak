#include "varak/renderer/rendering_context.h"
#include "varak/renderer/renderer.h"

#include "opengl/opengl_context.h"

namespace Varak {

    std::unique_ptr<RenderingContext> RenderingContext::create(void* window)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: //
            return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(window));
        }

        VR_CORE_ASSERT_MSG(false, "Unknown RendererAPI!");
        return nullptr;
    }

} // namespace Varak
