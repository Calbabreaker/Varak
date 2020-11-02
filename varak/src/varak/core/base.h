#pragma once

#include "log.h"

#ifdef VR_DEBUG
    // TODO: cross compiler/ide debug break
    // https://github.com/nemequ/portable-snippets/blob/master/debug-trap/debug-trap.h
    #ifdef _MSC_VER
        #define VR_DEBUGBREAK() __debugbreak()
    #else
        #error "Compiler/IDE does not support DebugBreak!"
    #endif

    // TODO: optional message param
    // https://stackoverflow.com/questions/3046889/optional-parameters-with-c-macros
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

namespace Varak {

    template <typename T>
    using Scope = std::unique_ptr<T>;
    template <typename T, typename... Args>
    constexpr Scope<T> makeScope(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using Ref = std::shared_ptr<T>;
    template <typename T, typename... Args>
    constexpr Ref<T> makeRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

} // namespace Varak