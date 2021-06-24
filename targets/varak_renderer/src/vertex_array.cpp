#include "vertex_array.h"
#include "renderer.h"

#include "opengl/opengl_vertex_array.h"

namespace Varak {

    Ref<VertexArray> VertexArray::create()
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: //
            return createRef<OpenGLVertexArray>();
        }

        VR_CORE_ASSERT_MSG(false, "Unknown RendererAPI!");
        return nullptr;
    }

} // namespace Varak
