#pragma once

#include "../rendering_context.h"

#include <GLFW/glfw3.h>

namespace Varak {

    class OpenGLContext : public RenderingContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        void init() override;
        void swapBuffers() override;

    private:
        GLFWwindow* m_windowHandle;
    };

} // namespace Varak
