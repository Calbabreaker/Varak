#include "platform/opengl/opengl_graphics_context.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Varak {

    OpenGLGraphicsContext::OpenGLGraphicsContext(GLFWwindow* windowHandle)
        : m_windowHandle(windowHandle)
    {
        VR_CORE_ASSERT(windowHandle, "Window handle is null!");
    }

    void OpenGLGraphicsContext::init()
    {
        glfwMakeContextCurrent(m_windowHandle);
        int status = gladLoadGLLoader(
            reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        VR_CORE_ASSERT(status, "Failed to initialize glad");
    }

    void OpenGLGraphicsContext::swapBuffers()
    {
        glfwSwapBuffers(m_windowHandle); //
    }

} // namespace Varak