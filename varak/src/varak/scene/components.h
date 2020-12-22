#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "varak/renderer/camera.h"

namespace Varak {

    struct IdentifierComponent
    {
        std::string name;

        IdentifierComponent() = default;
        IdentifierComponent(const std::string& name) : name(name) {}
    };

    struct TransformComponent
    {
        glm::vec3 translation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };
        glm::vec3 scale = { 1.0f, 1.0f, 1.0f };

        TransformComponent() = default;

        glm::mat4 getMatrix() const
        {
            glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), rotation.x, { 1.0f, 0.0f, 0.0f }) *
                                       glm::rotate(glm::mat4(1.0f), rotation.y, { 0.0f, 1.0f, 0.0f }) *
                                       glm::rotate(glm::mat4(1.0f), rotation.z, { 0.0f, 0.0f, 1.0f });

            return glm::translate(glm::mat4(1.0f), translation) * rotationMatrix * glm::scale(glm::mat4(1.0f), scale);
        }
    };

    struct SpriteRendererComponent
    {
        glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

        SpriteRendererComponent() = default;
        SpriteRendererComponent(const glm::vec4& color) : color(color) {}
    };

    struct CameraComponent : public Camera
    {
        bool fixedAspectRatio = false;
        bool primary = true; // TODO: move this into scene

        CameraComponent() = default;
    };

} // namespace Varak
