#pragma once

#include "varak_core.h"
#include <rttr/registration.h>

#define VR_COMPONENT_TEMPLATE_LIST                                                                 \
    <::Varak::SpriteRendererComponent, ::Varak::CameraComponent, ::Varak::TransformComponent>

namespace Varak {

    enum class ReflectMetaData
    {
        PrettyName,
    };

    // this component won't be shown in editor
    struct IdentifierComponent
    {
        std::string name;

        IdentifierComponent() = default;
        IdentifierComponent(const std::string& p_name) : name(p_name) {}
    };

} // namespace Varak
