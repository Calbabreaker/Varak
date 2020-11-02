#pragma once

namespace Varak {

    class RenderingContext
    {
    public:
        static Scope<RenderingContext> create(void* window);

        virtual ~RenderingContext() = default;

        virtual void init() = 0;
        virtual void swapBuffers() = 0;
    };

} // namespace Varak