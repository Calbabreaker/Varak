#pragma once

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

        bool m_isNameBeingEdited = false;
    };

} // namespace Varak
