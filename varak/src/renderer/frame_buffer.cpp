#include "varak/renderer/frame_buffer.h"
#include "varak/renderer/renderer.h"

#include "opengl/opengl_frame_buffer.h"

namespace Varak {

    std::shared_ptr<FrameBuffer> FrameBuffer::create(const FrameBufferProperties& props)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: //
            return std::make_shared<OpenGLFrameBuffer>(props);

        default: VR_CORE_ASSERT_MSG(false, "FrameBuffer unimplented for api!"); return nullptr;
        }
    }

} // namespace Varak
