#include "transform_component.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Varak {

    glm::mat4 TransformComponent::getMatrix() const
    {

        glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotation.x, { 1.0f, 0.0f, 0.0f }) *
                                   glm::rotate(glm::mat4(1.0f), rotation.y, { 0.0f, 1.0f, 0.0f }) *
                                   glm::rotate(glm::mat4(1.0f), rotation.z, { 0.0f, 0.0f, 1.0f });

        return glm::translate(glm::mat4(1.0f), translation) * rotationMatrix *
               glm::scale(glm::mat4(1.0f), scale);
    }

} // namespace Varak
