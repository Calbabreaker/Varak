#pragma once

#include "varak/core/timestep.h"

#include <entt.hpp>

namespace Varak {

    class Entity;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        void onUpdate(Timestep ts);

        Entity createEntity();
        void destroyEntity(Entity& entity);

    private:
        entt::registry m_registry;

        friend class Entity;
    };

} // namespace Varak
