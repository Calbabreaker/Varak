#pragma once

#include "varak_core.h"

namespace Varak {

    struct FrameBufferProperties
    {
        uint32_t width, height;
        uint32_t samples = 1;

        bool swapChainTarget = false;
    };

    class FrameBuffer
    {
    public:
        static Ref<FrameBuffer> create(const FrameBufferProperties& props);

        virtual ~FrameBuffer() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void resize(uint32_t width, uint32_t height) = 0;

        virtual uint32_t getColorAttachmentRendererID() = 0;
        virtual const FrameBufferProperties& getProperties() const = 0;
    };

} // namespace Varak
