#pragma once

#include "varak/renderer/vertex_array.h"

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
        virtual void clear() = 0;

        virtual void drawIndexed(const Ref<VertexArray>& vertexArray) = 0;

    private:
        static API s_API;
    };

} // namespace Varak