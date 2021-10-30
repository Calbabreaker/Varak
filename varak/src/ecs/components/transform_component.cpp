#include "varak/ecs/components/transform_component.h"
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

    VR_REFLECT
    {
        rttr::registration::class_<TransformComponent>("TransformComponent")(
            rttr::metadata(ReflectMetaData::PrettyName, "Transform"));
        // .property("translation", &TransformComponent::translation)(
        //     rttr::metadata(ReflectMetaData::PrettyName, "Translation"))
        // .property("rotation", &TransformComponent::rotation)(
        //     rttr::metadata(ReflectMetaData::PrettyName, "Rotation"))
        // .property("scale", &TransformComponent::scale)(
        //     rttr::metadata(ReflectMetaData::PrettyName, "Scale"));
    }

} // namespace Varak
