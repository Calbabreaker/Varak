#pragma once

#include "varak/renderer/rendering_context.h"

struct GLFWwindow;

namespace Varak {

    class OpenGLRenderingContext : public RenderingContext
    {
    public:
        OpenGLRenderingContext(GLFWwindow* windowHandle);

        void init() override;
        void swapBuffers() override;

    private:
        GLFWwindow* m_windowHandle;
    };

} // namespace Varak
