#pragma once

#include "inspector_panel/inspector_panel.h"

namespace Varak {

    class SceneHierarchyPanel
    {
    public:
        SceneHierarchyPanel(InspectorPanel* panel);

        void setScene(const std::shared_ptr<Scene>& scene);

        void onImGuiRender();

    private:
        void drawEntityNode(Entity entity);

    private:
        std::shared_ptr<Scene> m_scene;
        InspectorPanel* m_inspectorPanel;

        bool m_nameBeingEdited = false;
    };

} // namespace Varak
