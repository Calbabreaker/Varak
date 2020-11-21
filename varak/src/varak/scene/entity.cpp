#include "varak/scene/entity.h"

namespace Varak {

    Entity::Entity(entt::entity handle, Scene* scene)
        : m_handle(handle), m_scene(scene)
    {
    }

} // namespace Varak
