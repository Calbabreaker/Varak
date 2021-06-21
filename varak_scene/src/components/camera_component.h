#pragma once

#include "component.h"
#include "varak_renderer.h"

#include <glm/glm.hpp>

namespace Varak {

    struct CameraComponent : public Camera
    {
        bool fixedAspectRatio = false;
        bool primary = true; // TODO: move this into scene

        CameraComponent() = default;
    };

} // namespace Varak
