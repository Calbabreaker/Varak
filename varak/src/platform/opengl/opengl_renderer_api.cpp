#include "platform/opengl/opengl_renderer_api.h"

#include <glad/glad.h>

namespace Varak {

    namespace {

        void OpenGLMessageCallback(unsigned /*source*/, unsigned /*type*/,
                                   unsigned /*id*/, unsigned severity,
                                   int length, const char* message,
                                   const void* /*userParam*/)
        {
            switch (severity)
            {
            case GL_DEBUG_SEVERITY_LOW: VR_CORE_WARN(message); return;
            case GL_DEBUG_SEVERITY_MEDIUM: VR_CORE_ERROR(message); return;
            case GL_DEBUG_SEVERITY_HIGH: VR_CORE_CRITICAL(message); return;
            case GL_DEBUG_SEVERITY_NOTIFICATION: VR_CORE_TRACE(message); return;
            }

            VR_CORE_ASSERT(false, "Unknown severity level!");
        }

    } // namespace

    void OpenGLRendererAPI::init()
    {
#if VR_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLMessageCallback, nullptr);

        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE,
                              GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr,
                              GL_FALSE);
#endif
    }

    void OpenGLRendererAPI::setClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::drawIndexed(const Ref<VertexArray>& vertexArray)
    {
        glDrawElements(GL_TRIANGLES, vertexArray->getIndexBuffer()->getCount(),
                       GL_UNSIGNED_INT, nullptr);
    }

} // namespace Varak