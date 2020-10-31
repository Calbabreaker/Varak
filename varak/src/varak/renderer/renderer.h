#pragma once

namespace Varak {

    enum class RendererAPI
    {
        OpenGL
    };

    class Renderer
    {
    public:
        static RendererAPI getAPI() { return s_API; }

    private:
        static RendererAPI s_API;
    };

} // namespace Varak