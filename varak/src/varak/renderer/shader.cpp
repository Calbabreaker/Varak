#include "varak/renderer/shader.h"

#include "varak/renderer/renderer.h"

#include "platform/opengl/opengl_shader.h"

namespace Varak {

    std::shared_ptr<Shader> Shader::create(const std::string vertexSrc,
                                           const std::string fragmentSrc)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::OpenGL:
            return std::make_shared<OpenGLShader>(vertexSrc, fragmentSrc);
        }

        VR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

} // namespace Varak