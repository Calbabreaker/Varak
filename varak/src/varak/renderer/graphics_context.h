#pragma once

namespace Varak {

    class GraphicsContext
    {
    public:
        virtual void init() = 0;
        virtual void swapBuffers() = 0;

        static std::unique_ptr<GraphicsContext> create(void* window);
    };

} // namespace Varak