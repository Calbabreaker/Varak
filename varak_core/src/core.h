#pragma once

#include "assert.h"

#include <memory>

#define VR_BIT(x) (1 << x)
#define VR_UNUSED(...) (void)(__VA_ARGS__)
#define VR_BIND_FUNC(func)                                                                         \
    [this](auto&&... args) -> decltype(auto) {                                                     \
        return this->func(std::forward<decltype(args)>(args)...);                                  \
    }

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
