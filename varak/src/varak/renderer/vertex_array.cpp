#include "varak/renderer/vertex_array.h"

#include "varak/renderer/renderer.h"

#include "platform/opengl/opengl_vertex_array.h"

namespace Varak {

    Ref<VertexArray> VertexArray::create()
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL:
            return createRef<OpenGLVertexArray>();
        }

        VR_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }

} // namespace Varak
