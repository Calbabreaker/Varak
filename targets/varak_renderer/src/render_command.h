#pragma once

#include "renderer_api.h"

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
            s_rendererAPI->setClearColor(color); //
        };

        static void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            s_rendererAPI->setViewport(x, y, width, height);
        }

        static void clear()
        {
            s_rendererAPI->clear(); //
        };

        static void drawIndexed(const std::shared_ptr<VertexArray>& vertexArray,
                                uint32_t indexCount = 0)
        {
            s_rendererAPI->drawIndexed(vertexArray, indexCount);
        };

    private:
        inline static std::unique_ptr<RendererAPI> s_rendererAPI = RendererAPI::create();
    };

} // namespace Varak
