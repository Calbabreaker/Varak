#pragma once

#include "../frame_buffer.h"

namespace Varak {

    class OpenGLFrameBuffer : public FrameBuffer
    {
    public:
        OpenGLFrameBuffer(const FrameBufferProperties& props);
        ~OpenGLFrameBuffer();

        void invalidate();

        virtual void bind() override;
        virtual void unbind() override;

        void resize(uint32_t width, uint32_t height) override;

        uint32_t getColorAttachmentRendererID() override { return m_colorAttachment; }

        const FrameBufferProperties& getProperties() const override { return m_properties; }

    private:
        FrameBufferProperties m_properties;
        uint32_t m_rendererID;

        uint32_t m_colorAttachment;
        uint32_t m_depthAttachment;
    };

} // namespace Varak
