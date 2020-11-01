#pragma once

namespace Varak {

    enum class RendererAPI
    {
        None = 0, OpenGL
    };

    class Renderer
    {
    public:
        static RendererAPI getAPI() { return s_API; }

    private:
        static RendererAPI s_API;
    };

} // namespace Varak