#pragma once

#include "varak/scene/components.h"
#include "varak/scene/entity.h"
#include "varak/scene/scene.h"

#include "inspector_panel/inspector_panel.h"

namespace Varak {

    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel(InspectorPanel* panel);

        void setScene(const Ref<Scene>& scene);

        void onImGuiRender();

    private:
        void drawEntityNode(Entity entity);

    private:
        Ref<Scene> m_scene;
        InspectorPanel* m_inspectorPanel;
    };

} // namespace Varak
