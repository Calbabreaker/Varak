#include "platform/opengl/opengl_rendering_context.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Varak {

    OpenGLRenderingContext::OpenGLRenderingContext(GLFWwindow* windowHandle)
        : m_windowHandle(windowHandle)
    {
        VR_CORE_ASSERT_MSG(windowHandle, "Window handle is null!");
    }

    void OpenGLRenderingContext::init()
    {
        VR_PROFILE_FUNCTION();
      
        glfwMakeContextCurrent(m_windowHandle);
        int status = gladLoadGLLoader(
            reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        VR_CORE_ASSERT_MSG(status, "Failed to initialize glad!");

        VR_CORE_INFO("OpenGL Info: ");
        VR_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
        VR_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
        VR_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

        VR_CORE_ASSERT_MSG(GLVersion.major > 4 ||
                           (GLVersion.major == 4 && GLVersion.minor >= 5),
                       "Varak requires at least OpenGL version 4.5!");
    }

    void OpenGLRenderingContext::swapBuffers()
    {
        VR_PROFILE_FUNCTION();
      
        glfwSwapBuffers(m_windowHandle); 
    }

} // namespace Varak
