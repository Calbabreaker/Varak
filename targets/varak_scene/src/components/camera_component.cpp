#include "camera_component.h"

namespace Varak {

    void CameraComponent::temp() { void(); };

    RTTR_REGISTRATION
    {
        rttr::registration::class_<CameraComponent>("CameraComponent")(
            rttr::metadata(ReflectMetaData::PrettyName, "Camera"))
            .property("primary", &CameraComponent::primary)(
                rttr::metadata(ReflectMetaData::PrettyName, "Primary"))
            .property("fixedAspectRatio", &CameraComponent::fixedAspectRatio)(
                rttr::metadata(ReflectMetaData::PrettyName, "Fixed Aspect Ratio"));
    }

} // namespace Varak
