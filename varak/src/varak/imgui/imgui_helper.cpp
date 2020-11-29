#include "vrpch.h"

#include "imgui_helper.h"

#include <glm/glm.hpp>
#include <imgui.h>
#include <imgui_internal.h>

namespace Varak {

    namespace ImGuiHelper {

        void drawVec3Control(const std::string& label, glm::vec3& values, float resetValue, float columnWidth)
        {
            ImGuiIO& io = ImGui::GetIO();
            auto boldFont = io.Fonts->Fonts[0];

            ImGui::PushID(label.c_str());

            ImGui::Columns(2);
            ImGui::SetColumnWidth(0, columnWidth);
            ImGui::Text(label.c_str());
            ImGui::NextColumn();

            ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());

            ImGui::PushFont(boldFont);
            ImGui::Text("X");
            ImGui::PopFont();
            ImGui::SameLine();
            ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();
            ImGui::SameLine();

            ImGui::PushFont(boldFont);
            ImGui::Text("Y");
            ImGui::PopFont();
            ImGui::SameLine();
            ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();
            ImGui::SameLine();

            ImGui::PushFont(boldFont);
            ImGui::Text("Z");
            ImGui::PopFont();
            ImGui::SameLine();
            ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();

            ImGui::Columns(1);

            ImGui::PopID();
        }

    } // namespace EditorGui

} // namespace Varak
