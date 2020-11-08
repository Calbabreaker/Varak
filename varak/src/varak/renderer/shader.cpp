#include "varak/renderer/shader.h"

#include "varak/renderer/renderer.h"

#include "platform/opengl/opengl_shader.h"

namespace Varak {

    Ref<Shader> Shader::create(const std::string& vertexSrc,
                               const std::string& fragmentSrc)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL:
            return createRef<OpenGLShader>(vertexSrc, fragmentSrc);
        }

        VR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

} // namespace Varak
