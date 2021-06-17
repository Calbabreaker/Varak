#pragma once

#include "../renderer_api.h"

namespace Varak {

    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        void init() override;
        void setClearColor(const glm::vec4& color) override;
        void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
        void clear() override;

        void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
    };

} // namespace Varak
