#pragma once

#include "scene.h"

namespace Varak {

    class Entity
    {
    public:
        Entity() = default;
        Entity(entt::entity handle, Scene* scene) : m_handle(handle), m_scene(scene) {}

        template <typename T, typename... Args>
        T& addComponent(Args&&... args)
        {
            VR_CORE_ASSERT_MSG(!hasComponent<T>(), "Entity already has component!");
            T& component = m_scene->m_registry.emplace<T>(m_handle, std::forward<Args>(args)...);
            return component;
        }

        template <typename... T>
        decltype(auto) getComponent()
        {
            VR_CORE_ASSERT_MSG(hasAllComponents<T...>(), "Entity does not have the component!");
            return m_scene->m_registry.get<T...>(m_handle);
        }

        template <typename... T>
        auto tryGetComponent()
        {
            return m_scene->m_registry.try_get<T...>(m_handle);
        }

        template <typename... T>
        void removeComponent()
        {
            VR_CORE_ASSERT_MSG(hasAllComponents<T...>(), "Entity does not have the component!");
            return m_scene->m_registry.remove<T...>(m_handle);
        }

        template <typename... T>
        bool hasComponent()
        {
            return m_scene->m_registry.any_of<T...>(m_handle);
        }

        template <typename... T>
        bool hasAllComponents()
        {
            return m_scene->m_registry.all_of<T...>(m_handle);
        }

        operator entt::entity() { return m_handle; }
        operator bool() { return m_handle != entt::null; }
        operator uint32_t() { return static_cast<uint32_t>(m_handle); }

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
