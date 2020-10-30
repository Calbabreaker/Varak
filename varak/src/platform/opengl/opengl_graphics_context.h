#pragma once

#include "varak/renderer/graphics_context.h"

struct GLFWwindow;

namespace Varak {

    class OpenGLGraphicsContext : public GraphicsContext
    {
    public:
        OpenGLGraphicsContext(GLFWwindow* windowHandle);

        void init() override;
        void swapBuffers() override;

    private:
        GLFWwindow* m_windowHandle;
    };

} // namespace Varak