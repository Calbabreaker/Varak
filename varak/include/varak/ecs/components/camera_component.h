#pragma once

#include "varak/ecs/components/component.h"
#include "varak/math/camera.h"

namespace Varak {

    struct CameraComponent : public Camera
    {
        bool fixedAspectRatio = false;
        bool primary = true; // TODO: move this into scene

        CameraComponent() = default;
    };

} // namespace Varak
