#pragma once

#include "varak/renderer/renderer_api.h"

namespace Varak {

    class RenderCommand
    {
    public:
        static void init()
        {
            s_rendererAPI->init(); //
        };

        static void setClearColor(const glm::vec4& color)
        {
            s_rendererAPI->setClearColor(color);
        };

        static void clear()
        {
            s_rendererAPI->clear(); //
        };

        static void drawIndexed(const Ref<VertexArray>& vertexArray)
        {
            s_rendererAPI->drawIndexed(vertexArray);
        };

    private:
        static Scope<RendererAPI> s_rendererAPI;
    };

} // namespace Varak