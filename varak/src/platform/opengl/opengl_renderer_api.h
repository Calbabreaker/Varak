#pragma once

#include "varak/renderer/renderer_api.h"

namespace Varak {

    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        void init() override;
        void setClearColor(const glm::vec4& color) override;
        void clear() override;

        void drawIndexed(const Ref<VertexArray>& vertexArray) override;
    };

} // namespace Varak
