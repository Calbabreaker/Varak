#pragma once

namespace Varak {

    class RenderingContext
    {
    public:
        virtual void init() = 0;
        virtual void swapBuffers() = 0;

        static std::unique_ptr<RenderingContext> create(void* window);
    };

} // namespace Varak