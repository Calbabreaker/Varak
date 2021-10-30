#pragma once

#include "varak/ecs/components/component.h"

#include <glm/glm.hpp>

namespace Varak {

    struct TransformComponent
    {
        glm::vec3 translation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

        TransformComponent() = default;

        glm::mat4 getMatrix() const;
    };

} // namespace Varak
