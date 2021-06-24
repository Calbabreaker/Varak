#pragma once

#include "varak_core.h"
#include <refl.hpp>

namespace Varak {

    // this component won't be shown in editor
    struct IdentifierComponent
    {
        std::string name;

        IdentifierComponent() = default;
        IdentifierComponent(const std::string& p_name) : name(p_name) {}
    };

} // namespace Varak
