#pragma once

#include "varak/scene/scene.h"

namespace Varak {

    class Entity
    {
    public:
        Entity() = default;
        Entity(entt::entity handle, Scene* scene);

        template <typename Component, typename... Args>
        Component& addComponent(Args&&... args)
        {
            VR_CORE_ASSERT_MSG(!hasComponent<Component>(), "Entity already has component!");
            Component& component = m_scene->m_registry.emplace<Component>(m_handle, std::forward<Args>(args)...);
            m_scene->onComponentAdded<Component>(*this, component);
            return component;
        }

        template <typename Component>
        Component& getComponent()
        {
            VR_CORE_ASSERT_MSG(hasComponent<Component>(), "Entity does not have component!");
            return m_scene->m_registry.get<Component>(m_handle);
        }

        template <typename Component>
        void removeComponent()
        {
            VR_CORE_ASSERT_MSG(hasComponent<Component>(), "Entity does not have component!");
            return m_scene->m_registry.remove<Component>(m_handle);
        }

        template <typename Component>
        bool hasComponent()
        {
            return m_scene->m_registry.has<Component>(m_handle);
        }

        operator entt::entity() { return m_handle; }
        operator bool() { return m_handle != entt::null; }
        operator uint32_t() {return static_cast<uint32_t>(m_handle); }

        bool operator==(const Entity& other)
        {
            return m_handle == other.m_handle && m_scene == other.m_scene; //
        }

        bool operator!=(const Entity& other)
        {
            return !(*this == other); //
        }

    private:
        entt::entity m_handle = entt::null;
        Scene* m_scene = nullptr;
    };

} // namespace Varak
