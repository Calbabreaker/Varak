#include "vrpch.h"

#include "varak/renderer/framebuffer.h"

#include "varak/renderer/renderer.h"

#include "platform/opengl/opengl_framebuffer.h"

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
