#include "vrpch.h"

#include "varak/renderer/frame_buffer.h"

#include "varak/renderer/renderer.h"

#include "platform/opengl/opengl_frame_buffer.h"

namespace Varak {

    Ref<FrameBuffer> FrameBuffer::create(const FrameBufferProperties& props)
    {
        switch (Renderer::getAPI())
        {
        case RendererAPI::API::OpenGL: //
            return createRef<OpenGLFrameBuffer>(props);
        }

        VR_CORE_ASSERT_MSG(false, "Unknown RendererAPI!");
        return nullptr;
    }

} // namespace Varak
