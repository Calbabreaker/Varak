#include "sprite_renderer_component.h"

namespace Varak {

    RTTR_REGISTRATION
    {
        rttr::registration::class_<SpriteRendererComponent>("SpriteRendererComponent")(
            rttr::metadata(ReflectMetaData::PrettyName, "Sprite Renderer"))
            .property("color", &SpriteRendererComponent::color)(
                rttr::metadata(ReflectMetaData::PrettyName, "Color"));
    }

} // namespace Varak
