#pragma once

#include "varak/core/assert.h"
#include "varak/core/platform_detection.h"

#define VR_BIT(x) (1 << x)

#define VR_BIND_EVENT_FUNC(func) [this](auto&&... args) -> decltype(auto) { return this->func(std::forward<decltype(args)>(args)...); }

namespace Varak {

    template <typename T>
    using Scope = std::unique_ptr<T>;
    template <typename T, typename... Args>
    constexpr Scope<T> createScope(Args&&... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    using Ref = std::shared_ptr<T>;
    template <typename T, typename... Args>
    constexpr Ref<T> createRef(Args&&... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

} // namespace Varak
