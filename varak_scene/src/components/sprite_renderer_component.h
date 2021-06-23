#pragma once

#include "component.h"

#include <glm/glm.hpp>

namespace Varak {

    struct SpriteRendererComponent
    {
        glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

        SpriteRendererComponent() = default;
        SpriteRendererComponent(const glm::vec4& p_color) : color(p_color) {}
    };

} // namespace Varak

REFL_TYPE(Varak::SpriteRendererComponent)
REFL_FIELD(color)
REFL_END
