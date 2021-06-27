#include "inspector_panel.h"

#include <imgui.h>

namespace Varak {

    void InspectorPanel::onImGuiRender()
    {
        ImGui::Begin("Inspector");

        if (m_selectedItem.is_type<Entity>())
        {
            inspectItem(getSelected<Entity>());
        }

        ImGui::End();
    }

} // namespace Varak
