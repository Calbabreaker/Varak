#include "inspector_panel.h"

#include <imgui.h>

namespace Varak {

    void InspectorPanel::onImGuiRender()
    {
        ImGui::Begin("Inspector");

        if (auto entity = static_cast<Entity>(m_selectedInspectable))
        {
            drawProperties(entity);
        }

        ImGui::End();
    }

} // namespace Varak
