#pragma once

#include "components/camera_component.h"
#include "components/sprite_renderer_component.h"
#include "components/transform_component.h"
#include "editor_camera.h"
#include "varak_app.h"

#define ENTT_DISABLE_ASSERT
#include <entt/entt.hpp>

namespace Varak {

    class Entity;

    class Scene
    {
    public:
        Scene(uint32_t viewportWidth, uint32_t viewportHeight);
        ~Scene();

        void onUpdate(Timestep ts);
        void onRenderEditor(EditorCamera& camera);
        void onPlayRuntime();
        void onStopRuntime();
        void onRenderRuntime();

        void onViewportResize(uint32_t width, uint32_t height);

        Entity createEntity(const std::string& name = "Empty Entity");
        void destroyEntity(Entity entity);

    private:
        void onCameraComponentAdded(entt::registry& registry, entt::entity entity);

    private:
        entt::registry m_registry;

        uint32_t m_viewportWidth, m_viewportHeight;

        friend class Entity;
        friend class SceneHierarchyPanel;
    };

} // namespace Varak
