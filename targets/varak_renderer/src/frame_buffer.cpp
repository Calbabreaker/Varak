#include "frame_buffer.h"
#include "renderer.h"

#include "opengl/opengl_frame_buffer.h"

namespace Varak {

    std::shared_ptr<FrameBuffer> FrameBuffer::create(const FrameBufferProperties& props)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: //
            return std::make_shared<OpenGLFrameBuffer>(props);
        }

        VR_CORE_ASSERT_MSG(false, "Unknown RendererAPI!");
        return nullptr;
    }

} // namespace Varak
