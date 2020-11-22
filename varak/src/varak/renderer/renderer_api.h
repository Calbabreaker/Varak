#pragma once

#include "varak/renderer/vertex_array.h"

#include <glm/glm.hpp>

namespace Varak {

    class RendererAPI
    {
    public:
        enum class API
        {
            OpenGL
        };

    public:
        static Scope<RendererAPI> create();
        static API getAPI() { return s_API; }

        virtual ~RendererAPI() = default;

        virtual void init() = 0;
        virtual void setClearColor(const glm::vec4& color) = 0;
        virtual void setViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        virtual void clear() = 0;

        virtual void drawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

    private:
        static API s_API;
    };

} // namespace Varak
