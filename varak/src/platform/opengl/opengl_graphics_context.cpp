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

        VR_CORE_INFO("OpenGL Info: ");
        VR_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
        VR_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
        VR_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

        VR_CORE_ASSERT(GLVersion.major > 4 ||
                           (GLVersion.major == 4 && GLVersion.minor >= 5),
                       "Varak requires at least OpenGL version 4.5!");
    }

    void OpenGLGraphicsContext::swapBuffers()
    {
        glfwSwapBuffers(m_windowHandle); //
    }

} // namespace Varak