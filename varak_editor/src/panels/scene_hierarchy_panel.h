#pragma once

#include "varak/scene/components.h"
#include "varak/scene/entity.h"
#include "varak/scene/scene.h"

namespace Varak {

    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel() = default;

        void setScene(const Ref<Scene>& scene);

        void onImGuiRender();

    private:
        void drawEntityNode(Entity entity);
        void drawComponents(Entity entity);

    private:
        Ref<Scene> m_scene;

        Entity m_selectedEntity;
    };

} // namespace Varak
