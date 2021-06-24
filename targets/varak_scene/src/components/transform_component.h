#pragma once

#include "component.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Varak {

    struct TransformComponent
    {
        glm::vec3 translation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

        TransformComponent() = default;

        glm::mat4 getMatrix() const
        {

            glm::mat4 rotationMatrix =
                glm::rotate(glm::mat4(1.0f), rotation.x, { 1.0f, 0.0f, 0.0f }) *
                glm::rotate(glm::mat4(1.0f), rotation.y, { 0.0f, 1.0f, 0.0f }) *
                glm::rotate(glm::mat4(1.0f), rotation.z, { 0.0f, 0.0f, 1.0f });

            return glm::translate(glm::mat4(1.0f), translation) * rotationMatrix *
                   glm::scale(glm::mat4(1.0f), scale);
        }
    };

} // namespace Varak

REFL_TYPE(Varak::TransformComponent)
REFL_FIELD(translation)
REFL_FIELD(rotation)
REFL_FIELD(scale)
REFL_END
