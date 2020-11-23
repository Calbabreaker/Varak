#pragma once

#include <glm/glm.hpp>

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
        glm::mat4 transform = glm::mat4(1.0f);

        TransformComponent() = default;
        TransformComponent(const glm::mat4& transform) : transform(transform) {}
    };

    struct SpriteRendererComponent
    {
        glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

        SpriteRendererComponent() = default;
        SpriteRendererComponent(const glm::vec4& color) : color(color) {}
    };

    struct CameraComponent
    {
        Camera camera;
        bool fixedAspectRatio = false;
        bool primary = true; // TODO: move this into scene

        CameraComponent() = default;
    };

} // namespace Varak
