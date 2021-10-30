#pragma once

#include "varak/ecs/components/component.h"

#include <glm/glm.hpp>

namespace Varak {

    struct SpriteRendererComponent
    {
        glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

        SpriteRendererComponent() = default;
        SpriteRendererComponent(const glm::vec4& p_color) : color(p_color) {}
    };

} // namespace Varak
