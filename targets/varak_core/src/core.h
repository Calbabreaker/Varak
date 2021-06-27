#pragma once

#include "assert.h"

#include <rttr/registration.h>

#define VR_BIND_FUNC(func)                                                                         \
    [this](auto&&... args) -> decltype(auto) {                                                     \
        return this->func(std::forward<decltype(args)>(args)...);                                  \
    }

#define VR_REFLECT RTTR_REGISTRATION

namespace Varak {

    enum class ReflectMetaData
    {
        PrettyName
    };

} // namespace Varak
