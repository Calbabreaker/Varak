#pragma once

#include "varak/core/timestep.h"
#include "varak/renderer/editor_camera.h"

#include <entt.hpp>

namespace Varak {

    class Entity;

    class Scene
    {
    public:
        Scene(uint32_t viewportWidth, uint32_t viewportHeight);
        ~Scene();

        void onUpdateEditor(Timestep ts, EditorCamera& camera);
        void onPlayRuntime();
        void onStopRuntime();
        void onUpdateRuntime(Timestep ts);

        void onViewportResize(uint32_t width, uint32_t height);

        Entity createEntity(const std::string& name = "Empty Entity");
        void destroyEntity(Entity entity);

    private:
        template <typename Component>
        void onComponentAdded(Entity entity, Component& component);

    private:
        entt::registry m_registry;

        uint32_t m_viewportWidth, m_viewportHeight;

        friend class Entity;
        friend class SceneHierarchyPanel;
    };

} // namespace Varak
