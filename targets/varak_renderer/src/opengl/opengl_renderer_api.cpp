#include "opengl_renderer_api.h"

#include <glad/glad.h>

namespace Varak {

    namespace {

        void OpenGLMessageCallback(unsigned /*source*/, unsigned /*type*/, unsigned /*id*/,
                                   unsigned severity, int /*length*/, const char* message,
                                   const void* /*userParam*/)
        {
            switch (severity)
            {
            case GL_DEBUG_SEVERITY_LOW: VR_CORE_INFO(message); break;
            case GL_DEBUG_SEVERITY_MEDIUM: VR_CORE_WARN(message); break;
            case GL_DEBUG_SEVERITY_HIGH: VR_CORE_ERROR(message); break;
            case GL_DEBUG_SEVERITY_NOTIFICATION: VR_CORE_TRACE(message); break;
            default: VR_CORE_ASSERT_MSG(false, "Unknown severity level!"); break;
            }
        }

    } // namespace

    void OpenGLRendererAPI::init()
    {
#if VR_DEBUG
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(OpenGLMessageCallback, nullptr);

        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0,
                              nullptr, GL_FALSE);
#endif

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRendererAPI::setClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a); //
    }

    void OpenGLRendererAPI::setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
    {
        glViewport(static_cast<int>(x), static_cast<int>(y), static_cast<int>(width),
                   static_cast<int>(height));
    }

    void OpenGLRendererAPI::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //
    }

    void OpenGLRendererAPI::drawIndexed(const std::shared_ptr<VertexArray>& vertexArray,
                                        uint32_t indicesCount)
    {
        uint32_t count = indicesCount ? indicesCount : vertexArray->getIndexBuffer()->getCount();

        glDrawElements(GL_TRIANGLES, static_cast<int>(count), GL_UNSIGNED_SHORT, nullptr);
    }

} // namespace Varak
