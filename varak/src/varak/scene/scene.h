#pragma once

#include "varak/core/timestep.h"

#include <entt.hpp>

namespace Varak {

    class Entity;

    class Scene
    {
    public:
        Scene(uint32_t viewportWidth, uint32_t viewportHeight);
        ~Scene();

        void onUpdate(Timestep ts);

        void onViewportResize(uint32_t width, uint32_t height);

        Entity createEntity();
        void destroyEntity(Entity& entity);

    private:
        template <typename T>
        void onComponentAdded(Entity& entity, T& component);

    private:
        entt::registry m_registry;

        uint32_t m_viewportWidth, m_viewportHeight;

        friend class Entity;
    };

} // namespace Varak
