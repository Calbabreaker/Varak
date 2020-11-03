#pragma once

#include "varak/renderer/render_command.h"

namespace Varak {

    class Renderer
    {
    public:
        static RendererAPI::API getAPI() { return RendererAPI::getAPI(); }

        static void beginScene();
        static void endScene();

        static void submit(const Ref<VertexArray>& vertexArray);
    };

} // namespace Varak