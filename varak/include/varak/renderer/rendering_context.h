#pragma once

#include "varak/core/core.h"

namespace Varak {

    class RenderingContext
    {
    public:
        static std::unique_ptr<RenderingContext> create(void* window);

        virtual ~RenderingContext() = default;

        virtual void init() = 0;
        virtual void swapBuffers() = 0;
    };

} // namespace Varak
