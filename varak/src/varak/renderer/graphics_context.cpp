#include "varak/renderer/graphics_context.h"

#include "platform/opengl/opengl_graphics_context.h"

namespace Varak {

    std::unique_ptr<GraphicsContext> GraphicsContext::create(void* window)
    {
        return std::make_unique<OpenGLGraphicsContext>(
            reinterpret_cast<GLFWwindow*>(window));
    }

} // namespace Varak