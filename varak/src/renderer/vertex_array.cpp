#include "varak/renderer/vertex_array.h"
#include "varak/renderer/renderer.h"

#include "opengl/opengl_vertex_array.h"

namespace Varak {

    std::shared_ptr<VertexArray> VertexArray::create()
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: //
            return std::make_shared<OpenGLVertexArray>();
        }

        VR_CORE_ASSERT_MSG(false, "Unknown RendererAPI!");
        return nullptr;
    }

} // namespace Varak
