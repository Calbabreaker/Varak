#pragma once

#include "varak/scene/scene.h"

namespace Varak {

    class Entity
    {
    public:
        Entity() = default;
        Entity(entt::entity handle, Scene* scene);

        template <typename T, typename... Args>
        T& addComponent(Args&&... args)
        {
            VR_CORE_ASSERT_MSG(!hasComponent<T>(),
                               "Entity already has component!");
            return m_scene->m_registry.emplace<T>(m_handle, std::forward<Args>(args)...);
        }

        template <typename T>
        T& getComponent()
        {
            VR_CORE_ASSERT_MSG(hasComponent<T>(),
                               "Entity does not have component!");
            return m_scene->m_registry.get<T>(m_handle);
        }

        template <typename T>
        void removeComponent()
        {
            VR_CORE_ASSERT_MSG(hasComponent<T>(),
                               "Entity does not have component!");
            return m_scene->m_registry.remove<T>(m_handle);
        }

        template <typename T>
        bool hasComponent()
        {
            return m_scene->m_registry.has<T>(m_handle);
        }

        operator entt::entity() { return m_handle; }
        operator bool() { return m_handle != entt::null; }

        bool operator==(const Entity& other)
        {
            return m_handle == other.m_handle && m_scene == other.m_scene;
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
