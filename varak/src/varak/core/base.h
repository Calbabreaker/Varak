#pragma once

#include "log.h"

#ifdef VR_DEBUG
    #ifdef _MSC_VER
        #define VR_DEBUGBREAK() __debugbreak()
    #else
        #error "Compiler/IDE does not support DebugBreak!"
    #endif

    #define VR_CORE_ASSERT(expr, ...)                                          \
        if (!(expr))                                                           \
        VR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__), VR_DEBUGBREAK()

    #define VR_ASSERT(expr, ...)                                               \
        if (!(expr))                                                           \
        VR_ERROR("Assertion Failed: {0}", __VA_ARGS__), VR_DEBUGBREAK()
#else
    #define VR_CORE_ASSERT(expr, ...)
    #define VR_ASSERT(expr, ...)
    #define VR_DEBUGBREAK()
#endif

#define VR_BIT(x) (1 << x)

#define VR_BIND_EVENT_FUNC(func) std::bind(&func, this, std::placeholders::_1)